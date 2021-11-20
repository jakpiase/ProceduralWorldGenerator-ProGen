#include <glog/logging.h>
#include "src/pcg/utils/grid_utils.h"
#include "src/pcg/agent_generators/agents/look_ahead/utils/collision_utils.h"
#include "src/pcg/agent_generators/agents/look_ahead/recurring_look_ahead_agent.h"

void RecurringLookAheadAgent::run(Scene& scene, Grid& grid, RandomNumberGenerator& rng) {
    set_starting_position(grid, rng);


    unsigned int generation_number = 0;
    do {
        perform_generation(scene, grid, rng);
    } while (!visited_rooms_positions.empty() && ++generation_number < NUMBER_OF_GENERATIONS_ALLOWED);

    finish(scene, grid);
}

void RecurringLookAheadAgent::place_room(Scene& scene, Grid& grid, BoundingBox2i room_box, RandomNumberGenerator& rng) {
    LookAheadAgent::place_room(scene, grid, room_box, rng);

    room_excluded_from_corridor_collision.reset();
    if (!visited_rooms_positions.empty() && rng.random(100) <= recurse_chance) {
        perform_recursive_move(scene, grid, rng);
    } else {
        mark_current_position_as_visited();
        recurse_chance += RECURSE_CHANGE_INCREASE_PER_ROOM;
    }
}

void RecurringLookAheadAgent::perform_recursive_move(Scene& scene, Grid& grid, RandomNumberGenerator& rng) {
    go_to_previous_position(grid, rng);
    flush_rooms_buffer(scene, grid);
    recurse_chance = INITIAL_RECURSE_CHANCE;

    if (ALLOW_MULTIPLE_RETURNS) {
        mark_current_position_as_visited();
    }
}

void RecurringLookAheadAgent::mark_current_position_as_visited() {
    visited_rooms_positions.emplace_back(get_current_position());
}

void RecurringLookAheadAgent::go_to_previous_position(const Grid& grid, RandomNumberGenerator& rng) {
    unsigned int previous_position_index = rng.random(visited_rooms_positions.size());
    Point2i new_position = pop_previous_position_at_index(previous_position_index);

    DLOG(INFO) << "Going to previous position at " << new_position;

    set_current_position(new_position);
    BoundingBox2i current_room_box = GridUtils::bounding_box_from_position(grid, get_current_position());
    room_excluded_from_corridor_collision = std::make_unique<BoundingBox2i>(current_room_box);
}

Point2i RecurringLookAheadAgent::pop_previous_position_at_index(unsigned int index) {
    Point2i result = visited_rooms_positions[index];
    std::swap(visited_rooms_positions[index], visited_rooms_positions.back());
    visited_rooms_positions.pop_back();

    return result;
}

bool RecurringLookAheadAgent::can_place_corridor(Grid& grid, BoundingBox2i corridor_box, Point2i corridor_end) {
    return grid.contains(corridor_box) &&
           !CollisionUtils::collides_with(get_corridors_buffer(), corridor_box) &&
           !CollisionUtils::has_room_in_neumann_neighbourhood(grid, corridor_end) &&
           (room_excluded_from_corridor_collision ?
            CollisionUtils::is_empty(grid, corridor_box, *room_excluded_from_corridor_collision)
                                                  : CollisionUtils::is_empty(grid, corridor_box));
}