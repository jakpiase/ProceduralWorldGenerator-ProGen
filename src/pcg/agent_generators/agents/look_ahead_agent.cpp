#include <random>
#include <glog/logging.h>
#include <algorithm>
#include "src/pcg/agent_generators/agents/look_ahead_agent.h"
#include "src/pcg/utils/grid_to_entity_parser.h"
#include "src/pcg/agent_generators/agents/utils/spatial_iterators.h"

void LookAheadAgent::run(Scene& scene, Grid& grid, RandomNumberGenerator& rng) {
    position = get_starting_position(grid, rng);
    DLOG(INFO) << "Starting with position " << position;

    while (true) {
        if (try_to_place_room(scene, grid, rng)) {
        }

        if (corridors_buffer.size() >= MAX_CORRIDOR_SEEK_TIME
            || !try_to_place_corridor(scene, grid, rng)) {
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

void LookAheadAgent::place_room(Scene& scene, Grid& grid, BoundingBox2i room_box) {
    position = room_box.get_middle();
    flush_corridors_buffer(scene, grid);

    DLOG(INFO) << "Placed room " << room_box << " and updated position to " << position;
    DLOG(INFO) << grid << '\n';

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
    //it ignores starting coordinates - assumes its (0,0) - cause grid model does not keep them.
    return Point2i(
            static_cast<int>(rng.random(MIN_ROOM_SIZE, grid.get_width() - MIN_ROOM_SIZE)),
            static_cast<int>(rng.random(MIN_ROOM_SIZE, grid.get_height() - MIN_ROOM_SIZE))
    );
}

void LookAheadAgent::flush_rooms_buffer(Scene& scene, Grid& grid) {
    DLOG(INFO) << "Flushing rooms buffer";

    for (const BoundingBox2i& room_box: rooms_buffer) {
        grid.fill(room_box, GridElement::ROOM);
        DLOG(INFO) << "Added room\n" << grid << '\n';
    }

    rooms_buffer.clear();
}

void LookAheadAgent::flush_corridors_buffer(Scene& scene, Grid& grid) {
    DLOG(INFO) << "Flushing corridors buffer";

    for (const BoundingBox2i& corridor_box: corridors_buffer) {
        grid.fill_no_override(corridor_box, GridElement::CORRIDOR);
        DLOG(INFO) << "Added room\n" << grid << '\n';
    }

    corridors_buffer.clear();
}
