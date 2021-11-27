#pragma once
#include "src/pcg/grid.h"

class GridUtils {
public:
    [[nodiscard]] static BoundingBox2i bounding_box_from_position(const Grid& grid, const Point2i& position);
    static void create_straight_corridor(Grid& grid, const Point2i& a, const Point2i& b);

private:
    [[nodiscard]] static Point2i move_position_diagonally(const Grid& grid, const Point2i& position, int offset_x, int offset_y);
};



