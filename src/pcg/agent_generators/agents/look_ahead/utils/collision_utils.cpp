#include "src/pcg/agent_generators/agents/look_ahead/utils/collision_utils.h"
#include <algorithm>

bool CollisionUtils::collides_with(const std::vector<BoundingBox2i>& boxes, const BoundingBox2i& box) {
    return std::ranges::any_of(boxes, [box](const BoundingBox2i& box_from_vector) {
        return box.collides_with(box_from_vector);
    });
}

bool CollisionUtils::has_room_in_neumann_neighbourhood(const Grid& grid, const Point2i& point) {
    return std::ranges::any_of(grid.get_neumann_neighbourhood(point.y, point.x), [](const GridElement& element){
        return element == GridElement::ROOM;
    });
}

bool CollisionUtils::is_empty(Grid& grid, const BoundingBox2i& box) {
    return std::ranges::all_of(grid.begin(box), grid.end(box), [](const GridElement& elem) {
        return elem == GridElement::EMPTY;
    });
}

bool CollisionUtils::is_empty_or_has_corridor(Grid& grid, const BoundingBox2i& box) {
    return std::ranges::all_of(grid.begin(box), grid.end(box), [](const GridElement& elem) {
        return elem == GridElement::EMPTY || elem == GridElement::CORRIDOR;
    });
}
