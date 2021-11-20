#pragma once
#include "src/pcg/grid.h"

class CollisionUtils {
public:
    static bool collides_with(const std::vector<BoundingBox2i>& boxes, const BoundingBox2i& box);
    static bool has_room_in_neumann_neighbourhood(const Grid& grid, const Point2i& point);
    static bool is_empty(Grid& grid, const BoundingBox2i& box);
    static bool is_empty(const Grid& grid, const BoundingBox2i& box, const BoundingBox2i& exclusion);
    static bool is_empty_or_has_corridor(Grid& grid, const BoundingBox2i& box);
};



