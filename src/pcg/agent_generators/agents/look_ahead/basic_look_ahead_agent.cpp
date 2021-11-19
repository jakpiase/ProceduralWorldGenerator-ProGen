#include "src/pcg/agent_generators/agents/look_ahead/utils/collision_utils.h"
#include "src/pcg/agent_generators/agents/look_ahead/basic_look_ahead_agent.h"

bool BasicLookAheadAgent::can_place_corridor(Grid& grid, BoundingBox2i corridor_box, Point2i corridor_end) {
    return grid.contains(corridor_box) &&
        !CollisionUtils::collides_with(get_corridors_buffer(), corridor_box) &&
        CollisionUtils::is_empty(grid, corridor_box);
}
