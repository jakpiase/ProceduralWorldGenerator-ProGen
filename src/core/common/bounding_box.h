#pragma once

#include "src/core/common/point.h"

class BoundingBox {

private:
    Point top_left;
    Point bottom_right;

public:
    BoundingBox(Point top_left, Point bottom_right);

    [[nodiscard]] static BoundingBox from_zero(float width, float height);

    [[nodiscard]] Point get_top_left() const;

    [[nodiscard]] Point get_top_right() const;

    [[nodiscard]] Point get_bottom_right() const;

    [[nodiscard]] Point get_bottom_left() const;

    [[nodiscard]] Point get_middle() const;

    [[nodiscard]] float get_width() const;

    [[nodiscard]] float get_height() const;

    friend std::ostream& operator<<(std::ostream& stream, const BoundingBox& bounding_box);
};

