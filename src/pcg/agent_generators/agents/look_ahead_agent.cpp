#include <vector>
#include <cstdlib>
#include <random>
#include <glog/logging.h>
#include <algorithm>
#include "src/pcg/agent_generators/agents/look_ahead_agent.h"
#include "src/pcg/utils/grid_to_entity_parser.h"
#include "src/pcg/utils/direction.h"
#include "src/pcg/utils/entity_creator.h"

std::vector<int> fill_vector_with_range(int from, int to);

template<typename T>
class RandomIterator {
    RandomNumberGenerator& rng;
    std::vector<T> elements;
    int index = 0;

public:
    explicit RandomIterator(std::vector<T>&& elements, RandomNumberGenerator& rng)
            : rng(rng),
              elements(std::move(elements)) {
        shuffle();
    }

    T next(bool should_increment = true) {
        assert((has_next()));

        return elements[should_increment ? index++ : index];
    }

    bool has_next() {
        return index < elements.size();
    }

    void reset() {
        index = 0;
        shuffle();
    }


private:
    void shuffle() {
        auto random_number_engine = std::default_random_engine(rng.random());
        std::shuffle(elements.begin(), elements.end(), random_number_engine);
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

        if (should_reset_first) {
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
    RoomIterator(int min_size, int max_size, RandomNumberGenerator& rng)
            : room_size_iterator(RandomIterator<int>(fill_vector_with_range(min_size, max_size), rng),
                                 RandomIterator<int>(fill_vector_with_range(min_size, max_size), rng)) {}

    Dimensions2i next() {
        std::pair<int, int> room_size = room_size_iterator.next();
        return {room_size.first, room_size.second};
    }

    bool has_next() {
        return room_size_iterator.has_next();
    }
};

class CorridorIterator {
    RandomIteratorPair<int, Direction> corridor_iterator;

public:
    CorridorIterator(int min_size, int max_size, RandomNumberGenerator& rng)
            : corridor_iterator(RandomIterator<int>(fill_vector_with_range(min_size, max_size), rng),
                                RandomIterator<Direction>(std::vector(DIRECTIONS.begin(), DIRECTIONS.end()), rng)) {}

    std::pair<int, Direction> next() {
        return corridor_iterator.next();
    }

    bool has_next() {
        return corridor_iterator.has_next();
    }
};


void LookAheadAgent::run(Scene& scene, Grid& grid, RandomNumberGenerator& rng) {
    position = get_starting_position(grid, rng);
    //BBoxGridWrapper bbox_grid(grid);
    DLOG(INFO) << "Starting with position " << position;

    while (true) {
        if (try_to_place_room(scene, grid, rng)) {
            corridor_seek_time = 0;
        } else {
            corridor_seek_time++;
        }

        if (corridor_seek_time > MAX_CORRIDOR_SEEK_TIME || !try_to_place_corridor(scene, grid, rng)) {
            break;
        }
    }

    finish(scene, grid);
}


bool LookAheadAgent::try_to_place_room(Scene& scene, Grid& grid, RandomNumberGenerator& rng) {
    RoomIterator room_iterator(MIN_ROOM_SIZE, MAX_ROOM_SIZE, rng);

    while (room_iterator.has_next()) {
        BoundingBox2i room_box = BoundingBox2i::from_dimensions_centered(position, room_iterator.next());
        if (can_place_room(grid, room_box)) {
            place_room(scene, grid, room_box);
            return true;
        }
    }
    DLOG(INFO) << "Could not place any room";

    return false;
}

bool LookAheadAgent::try_to_place_room(Scene& scene, BBoxGridWrapper& bbox_grid, RandomNumberGenerator& rng) {
    RoomIterator room_iterator(MIN_ROOM_SIZE, MAX_ROOM_SIZE, rng);

    while (room_iterator.has_next()) {
        BoundingBox2i room_box = BoundingBox2i::from_dimensions_centered(position, room_iterator.next());

        if (can_place_room(bbox_grid, room_box)) {
            place_room(scene, bbox_grid, room_box);
            return true;
        }
    }
    DLOG(INFO) << "Could not place any room";

    return false;
}

bool LookAheadAgent::can_place_room(Grid& grid, BoundingBox2i room_box) {
    if (!grid.contains(room_box)) {
        return false;
    }

    const BoundingBox2i grown_box = room_box.grown_by(1);
    const BoundingBox2i room_surrounding_box = grid.get_bounding_box().common_part_with(grown_box);
    return std::ranges::all_of(grid.begin(room_surrounding_box), grid.end(room_surrounding_box),
                               [](const GridElement& elem) {
                                   return elem == GridElement::EMPTY;
                               });
}

bool LookAheadAgent::can_place_room(BBoxGridWrapper& bbox_grid, BoundingBox2i room_box) {
    return std::ranges::none_of(bbox_grid.begin(), bbox_grid.end(), [room_box](const GridBox& grid_box) {
        return grid_box.box.collides_with(room_box);
    });
}

void LookAheadAgent::place_room(Scene& scene, Grid& grid, BoundingBox2i room_box) {
    position = room_box.get_middle();
    flush_corridors_buffer(scene, grid);

    DLOG(INFO) << "Placed room " << room_box << " and updated position to " << position;
    DLOG(INFO) << grid << '\n';

    rooms_buffer.emplace_back(room_box);
}

void LookAheadAgent::place_room(Scene& scene, BBoxGridWrapper& bbox_grid, BoundingBox2i room_box) {
    position = room_box.get_middle();
    flush_corridors_buffer(scene, bbox_grid);

    DLOG(INFO) << "Placed room " << room_box << " and updated position to " << position;

    rooms_buffer.emplace_back(room_box);
}

bool LookAheadAgent::try_to_place_corridor(Scene& scene, Grid& grid, RandomNumberGenerator& rng) {
    CorridorIterator corridor_iterator(MIN_CORRIDOR_LENGTH, MAX_CORRIDOR_LENGTH, rng);

    while (corridor_iterator.has_next()) {
        auto[length, direction] = corridor_iterator.next();
        auto[corridor_box, new_position] = get_corridor_box_with_updated_position(length, direction);

        if (can_place_corridor(grid, corridor_box, new_position)) {
            place_corridor(scene, grid, corridor_box, new_position);
            return true;
        }
    }
    DLOG(INFO) << "Could not place any corridor";

    return false;
}

bool LookAheadAgent::can_place_corridor(Grid& grid, BoundingBox2i corridor_box, Point2i corridor_end) {
    return grid.contains(corridor_box) &&
           std::ranges::none_of(corridors_buffer, [corridor_box](const BoundingBox2i& box) {
               return corridor_box.collides_with(box);
           }) &&
           std::ranges::none_of(grid.get_neumann_neighbourhood(corridor_end.y, corridor_end.x), [](const GridElement& element){
               return element == GridElement::ROOM;
           }) &&
           std::ranges::all_of(grid.begin(corridor_box), grid.end(corridor_box), [](const GridElement& elem) {
               return elem == GridElement::EMPTY || elem == GridElement::CORRIDOR;
           });
}

void LookAheadAgent::place_corridor(Scene& scene, Grid& grid, BoundingBox2i corridor_box, Point2i new_position) {
    position = new_position;
    flush_rooms_buffer(scene, grid);

    BoundingBox2i adjusted_corridor_box = BoundingBox2i(corridor_box.get_top_left(),
                                                        corridor_box.get_bottom_right().shifted_by(0, 0));
    corridors_buffer.emplace_back(adjusted_corridor_box);

    DLOG(INFO) << "Placed corridor " << adjusted_corridor_box << " and updated position to " << position;
    DLOG(INFO) << grid << '\n';
}

void LookAheadAgent::finish(Scene& scene, Grid& grid) {
    flush_rooms_buffer(scene, grid);

    GridToEntityParser(grid, scene).parse();

    DLOG(INFO) << "Agent job finished";
}

std::pair<BoundingBox2i, Point2i>
LookAheadAgent::get_corridor_box_with_updated_position(int length, Direction direction) {
    Point2i starting_position;
    Point2i next_position;
    BoundingBox2i box;

    switch (direction) {
        case Direction::Left:
            starting_position = position.shifted_by(-1, 0);
            next_position = position.shifted_by(-length, 0);
            box = BoundingBox2i(next_position, starting_position);
            break;
        case Direction::Top:
            starting_position = position.shifted_by(0, -1);
            next_position = position.shifted_by(0, -length);
            box = BoundingBox2i(next_position, starting_position);
            break;
        case Direction::Right:
            starting_position = position.shifted_by(1, 0);
            next_position = position.shifted_by(length, 0);
            box = BoundingBox2i(starting_position, next_position);
            break;
        case Direction::Bottom:
            starting_position = position.shifted_by(0, 1);
            next_position = position.shifted_by(0, length);
            box = BoundingBox2i(starting_position, next_position);
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

    for (const BoundingBox2i& room_box: rooms_buffer) {
        grid.fill(room_box, GridElement::ROOM);
        DLOG(INFO) << "Added room\n" << grid << '\n';
        //EntityCreatorImpl::create_room_floor(scene, room_box);
    }

    rooms_buffer.clear();
}

void LookAheadAgent::flush_corridors_buffer(Scene& scene, Grid& grid) {
    DLOG(INFO) << "Flushing corridors buffer";

    for (const BoundingBox2i& corridor_box: corridors_buffer) {
        grid.fill_no_override(corridor_box, GridElement::CORRIDOR);
        DLOG(INFO) << "Added room\n" << grid << '\n';
        //EntityCreatorImpl::create_corridor_floor(scene, corridor_box);
    }

    corridors_buffer.clear();
}

void LookAheadAgent::flush_corridors_buffer(Scene& scene, BBoxGridWrapper& bbox_grid) {
    DLOG(INFO) << "Flushing corridors buffer";

    for (const BoundingBox2i corridor_box: corridors_buffer) {
        bbox_grid.add(corridor_box, GridElement::CORRIDOR);
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
