#pragma once
#include "src/core/common/point.h"
#include "src/core/common/dimensions.h"

class BoundingBox {

private:
    Point top_left;
    Point bottom_right;

public:
    BoundingBox(Point top_left, Point bottom_right);

    BoundingBox(Point position, Dimensions2f dimensions);

    [[nodiscard]] static BoundingBox from_zero(float width, float height);

    [[nodiscard]] static BoundingBox from_dimensions(Point top_left, Dimensions2f dimensions);

    [[nodiscard]] Point get_top_left() const;

    [[nodiscard]] Point get_top_right() const;

    [[nodiscard]] Point get_bottom_right() const;

    [[nodiscard]] Point get_bottom_left() const;

    [[nodiscard]] Point get_middle() const;

    [[nodiscard]] float get_width() const;

    [[nodiscard]] float get_height() const;

    [[nodiscard]] Dimensions2f get_dimensions() const;

    friend std::ostream& operator<<(std::ostream& stream, const BoundingBox& bounding_box);

    static int manhattan_distance(const BoundingBox& first, const BoundingBox& second);
};

