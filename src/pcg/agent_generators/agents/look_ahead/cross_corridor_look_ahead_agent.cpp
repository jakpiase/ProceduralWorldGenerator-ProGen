#include "src/pcg/agent_generators/agents/look_ahead/utils/collision_utils.h"
#include "src/pcg/agent_generators/agents/look_ahead/cross_corridor_look_ahead_agent.h"

bool CrossCorridorLookAheadAgent::can_place_corridor(Grid& grid, BoundingBox2i corridor_box, Point2i corridor_end) {
    return grid.contains(corridor_box) &&
           !CollisionUtils::collides_with(get_corridors_buffer(), corridor_box) &&
           !CollisionUtils::has_room_in_neumann_neighbourhood(grid, corridor_end) &&
           CollisionUtils::is_empty_or_has_corridor(grid, corridor_box);
}
