#include <vector>
#include <cstdlib>
#include <random>
#include <glog/logging.h>
#include <algorithm>
#include "src/pcg/agent_generators/agents/look_ahead_agent.h"
#include "src/pcg/utils/direction.h"
#include "src/pcg/utils/entity_creator.h"

std::vector<int> fill_vector_with_range(int from, int to);

template<typename T>
class RandomIterator {
    std::vector<T> elements;
    int index = 0;

public:
    explicit RandomIterator(std::vector<T>&& elements) : elements(std::move(elements)) {}

    T next(bool should_increment = true) {
        assert((has_next()));

        return elements[should_increment ? index++ : index];
    }

    bool has_next(){
        return index < elements.size();
    }

    void reset(){
        index = 0;
        shuffle();
    }


private:
    void shuffle() {
//        auto rd = std::random_device{};
//        auto rng = std::default_random_engine{rd()};
//        std::shuffle(elements.begin(), elements.end(), rng);
    }

};

template<typename T, typename K>
class RandomIteratorPair {
    RandomIterator<T> first;
    RandomIterator<K> second;


public:
    RandomIteratorPair(RandomIterator<T>&& first, RandomIterator<K>&& second)
            : first(std::move(first)), second(std::move(second)) {}

    std::pair<T, K> next() {
        const T first_result = first.next();
        const bool should_reset_first = !first.has_next();
        const K second_result = second.next(should_reset_first);

        if(should_reset_first){
            first.reset();
        }

        return std::make_pair(first_result, second_result);
    }

    bool has_next() {
        return second.has_next();
    }
};

class RoomIterator {
    RandomIteratorPair<int, int> room_size_iterator;

public:
    RoomIterator(int min_size, int max_size)
            : room_size_iterator(RandomIterator<int>(fill_vector_with_range(min_size, max_size)),
                                 RandomIterator<int>(fill_vector_with_range(min_size, max_size))) {}

    Dimensions2i next() {
        std::pair<int, int> room_size = room_size_iterator.next();
        return Dimensions(room_size.first, room_size.second);
    }

    bool has_next() {
        return room_size_iterator.has_next();
    }
};

class CorridorIterator {
    RandomIteratorPair<int, Direction> corridor_iterator;

public:
    CorridorIterator(int min_size, int max_size)
            : corridor_iterator(RandomIterator<int>(fill_vector_with_range(min_size, max_size)),
                                RandomIterator<Direction>(std::vector(DIRECTIONS.begin(), DIRECTIONS.end()))) {}

    std::pair<int, Direction> next() {
        return corridor_iterator.next();
    }

    bool has_next() {
        return corridor_iterator.has_next();
    }
};


void LookAheadAgent::run(Scene& scene, Grid& grid, RandomNumberGenerator& rng) {
    position = get_starting_position(grid, rng);
    DLOG(INFO) << "Starting with position " << position;

    while (true) {
        try_to_place_room(scene, grid);
        if (!try_to_place_corridor(scene, grid)) {
            break;
        }
    }

    finish(scene, grid);
}


bool LookAheadAgent::try_to_place_room(Scene& scene, Grid& grid) {
    RoomIterator room_iterator(MIN_ROOM_SIZE, MAX_ROOM_SIZE);

    while (room_iterator.has_next()) {
        BoundingBox2i room_box = BoundingBox2i::from_dimensions_centered(position, room_iterator.next());

        DLOG(INFO) << "Trying to place room: " << room_box;
        if (can_place_room(grid, room_box)) {
            place_room(scene, grid, room_box);
            return true;
        }
    }
    DLOG(INFO) << "Could not place any room";

    return false;
}

bool LookAheadAgent::can_place_room(Grid& grid, BoundingBox2i corridor_box) {
    return grid.contains(corridor_box) &&
           std::ranges::all_of(grid.begin(corridor_box), grid.end(corridor_box), [](const GridElement& elem) {
               return elem == GridElement::EMPTY;
           });
}

void LookAheadAgent::place_room(Scene& scene, Grid& grid, BoundingBox2i room_box) {
    position = room_box.get_middle();
    flush_corridors_buffer(scene, grid);

    DLOG(INFO) << "Placed room " << room_box << " and updated position to " << position;

    areas_to_place.emplace_back(room_box, GridElement::ROOM);
}

bool LookAheadAgent::try_to_place_corridor(Scene& scene, Grid& grid) {
    CorridorIterator corridor_iterator(MIN_CORRIDOR_LENGTH, MAX_CORRIDOR_LENGTH);

    while (corridor_iterator.has_next()) {
        auto[length, direction] = corridor_iterator.next();
        auto[corridor_box, new_position] = get_corridor_box_with_updated_position(length, direction);

        DLOG(INFO) << "Trying to place corridor: " << corridor_box;
        if (can_place_corridor(grid, corridor_box)) {
            place_corridor(scene, grid, corridor_box, new_position);
            return true;
        }
    }
    DLOG(INFO) << "Could not place any corridor";

    return false;
}

bool LookAheadAgent::can_place_corridor(Grid& grid, BoundingBox2i corridor_box) {
    return grid.contains(corridor_box) &&
           std::ranges::all_of(grid.begin(corridor_box), grid.end(corridor_box), [](const GridElement& elem) {
               return elem == GridElement::EMPTY || elem == GridElement::CORRIDOR;
           });
}

void LookAheadAgent::place_corridor(Scene& scene, Grid& grid, BoundingBox2i corridor_box, Point2i new_position) {
    position = new_position;
    flush_rooms_buffer(scene, grid);


    BoundingBox2i adjusted_corridor_box = BoundingBox2i(corridor_box.get_top_left(),
                                                        corridor_box.get_bottom_right().shifted_by(0, 1));
    areas_to_place.emplace_back(adjusted_corridor_box, GridElement::CORRIDOR);

    DLOG(INFO) << "Placed corridor " << adjusted_corridor_box << " and updated position to " << position;
}

void LookAheadAgent::finish(Scene& scene, Grid& grid) {
    flush_rooms_buffer(scene, grid);

    DLOG(INFO) << "Agent job finished";
}

std::pair<BoundingBox2i, Point2i>
LookAheadAgent::get_corridor_box_with_updated_position(int length, Direction direction) {
    Point2i next_position;
    BoundingBox2i box;

    switch (direction) {
        case Direction::Left:
            next_position = position.shifted_by(-length, 0);
            box = BoundingBox2i(next_position, position);
            break;
        case Direction::Top:
            next_position = position.shifted_by(0, -length);
            box = BoundingBox2i(next_position, position);
            break;
        case Direction::Right:
            next_position = position.shifted_by(length, 0);
            box = BoundingBox2i(position, next_position);
            break;
        case Direction::Bottom:
            next_position = position.shifted_by(0, length);
            box = BoundingBox2i(position, next_position);
            break;
    }

    return std::make_pair(box, next_position);
}

Point2i LookAheadAgent::get_starting_position(const Grid& grid, RandomNumberGenerator& rng) const {
    //FIXME: it ignores starting coordinates - assumes its (0,0) - cause grid model does not keep them.
    return Point2i(
            rng.random(MIN_ROOM_SIZE, grid.get_width() - MIN_ROOM_SIZE),
            rng.random(MIN_ROOM_SIZE, grid.get_height() - MIN_ROOM_SIZE)
    );
}

void LookAheadAgent::flush_rooms_buffer(Scene& scene, Grid& grid) {
    DLOG(INFO) << "Flushing rooms buffer";

    for(const BoundingBox2i& room_box : rooms_buffer){
        grid.fill(room_box, GridElement::ROOM);
        //EntityCreatorImpl::create_room_floor(scene, room_box);
    }

    rooms_buffer.clear();
}

void LookAheadAgent::flush_corridors_buffer(Scene& scene, Grid& grid) {
    DLOG(INFO) << "Flushing corridors buffer";

    for(const BoundingBox2i corridor_box : corridors_buffer){
        grid.fill_no_override(corridor_box, GridElement::CORRIDOR);
        //EntityCreatorImpl::create_corridor_floor(scene, corridor_box);
    }

    corridors_buffer.clear();
}


std::vector<int> fill_vector_with_range(int from, int to) {
    int size = to - from + 1;
    std::vector<int> result;
    result.reserve(size);

    for (int i = from; i <= to; ++i) {
        result.push_back(i);
    }

    return result;
}
