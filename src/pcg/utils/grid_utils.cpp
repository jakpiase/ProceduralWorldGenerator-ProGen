#include <cassert>
#include "src/pcg/utils/grid_utils.h"

BoundingBox2i GridUtils::bounding_box_from_position(const Grid& grid, const Point2i& position) {
    Point2i top_left = move_position_diagonally(grid, position, -1, -1);
    Point2i bottom_right = move_position_diagonally(grid, position, 1, 1);

    return BoundingBox(top_left, bottom_right);
}

void GridUtils::create_straight_corridor(Grid& grid, const Point2i& a, const Point2i& b) {
    assert((a.x == b.x || a.y == b.y));

    const Point2i start(std::min(a.x, b.x), std::min(a.y, b.y));
    const Point2i end(std::max(a.x, b.x), std::max(a.y, b.y));
    const BoundingBox2i corridor_box(start, end);

    grid.fill_no_override(corridor_box, GridElement::CORRIDOR);
}


Point2i GridUtils::move_position_diagonally(const Grid& grid, const Point2i& position, int offset_x, int offset_y) {
    const GridElement element = grid(position);

    Point2i result;
    Point2i tmp_point = position;

    do {
        result = tmp_point;
        tmp_point = tmp_point.shifted_by(offset_x, offset_y);
    } while (grid.contains(tmp_point) && grid(tmp_point) == element);

    tmp_point = result.shifted_by(offset_x, 0);
    if (grid.contains(tmp_point) && grid(tmp_point) == element) {
        result = tmp_point;
    }

    tmp_point = result.shifted_by(0, offset_y);
    if (grid.contains(tmp_point) && grid(tmp_point) == element) {
        result = tmp_point;
    }

    return result;
}
