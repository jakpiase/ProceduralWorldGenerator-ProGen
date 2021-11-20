#include "src/pcg/utils/grid_utils.h"

BoundingBox2i GridUtils::bounding_box_from_position(const Grid& grid, const Point2i& position) {
    Point2i top_left = move_position_diagonally(grid, position, -1, -1);
    Point2i bottom_right = move_position_diagonally(grid, position, 1, 1);

    return BoundingBox(top_left, bottom_right);
}

Point2i GridUtils::move_position_diagonally(const Grid& grid, const Point2i& position, int offset_x, int offset_y) {
    const GridElement element = grid(position);

    Point2i result;
    Point2i tmp_point = position;

    do {
        result = tmp_point;
        tmp_point = tmp_point.shifted_by(offset_x, offset_y);
    } while (grid.contains(tmp_point) && grid(tmp_point) == element);

    return result;
}
