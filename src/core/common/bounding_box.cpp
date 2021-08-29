#include "src/core/common/bounding_box.h"

BoundingBox::BoundingBox(Point top_left, Point bottom_right)
        : top_left(top_left),
          bottom_right(bottom_right) {}

BoundingBox BoundingBox::from_zero(float width, float height) {
    return BoundingBox(Point(0, 0), Point(width, height));
}

BoundingBox BoundingBox::from_dimensions(Point top_left, Dimensions2f dimensions) {
    return BoundingBox(top_left, top_left.shifted_by(dimensions.width, dimensions.height));
}

Point BoundingBox::get_bottom_left() const {
    return Point(top_left.x, bottom_right.y);
}

Point BoundingBox::get_top_left() const {
    return top_left;
}

Point BoundingBox::get_bottom_right() const {
    return bottom_right;
}

Point BoundingBox::get_top_right() const {
    return Point(bottom_right.x, top_left.y);
}

float BoundingBox::get_width() const {
    return bottom_right.x - top_left.x;
}

float BoundingBox::get_height() const {
    return bottom_right.y - top_left.y;
}

Point BoundingBox::get_middle() const {
    const float x = (top_left.x + bottom_right.x) / 2.0f;
    const float y = (top_left.y + bottom_right.y) / 2.0f;
    return Point(x, y);
}

Dimensions2f BoundingBox::get_dimensions() const {
    return Dimensions2f(get_width(), get_height());
}

