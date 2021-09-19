#include "src/core/common/bounding_box.h"

BoundingBox::BoundingBox(Point top_left, Point bottom_right)
        : top_left(top_left),
          bottom_right(bottom_right) {}

BoundingBox::BoundingBox(Point position, Dimensions2f dimensions)
        : top_left(position), 
          bottom_right(Point(position.x + dimensions.width, position.y + dimensions.height)) {}

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

std::ostream& operator<<(std::ostream& stream, const BoundingBox& bounding_box) {
    stream << "((" << bounding_box.top_left << ") ";
    stream << "(" << bounding_box.bottom_right << "))";
    return stream;
 }
 
int BoundingBox::manhattan_distance(const BoundingBox& first, const BoundingBox& second) {
    const float first_x1 = first.get_top_left().x;
    const float first_y1 = first.get_top_left().y;
    const float first_x2 = first.get_bottom_right().x;
    const float first_y2 = first.get_bottom_right().y;

    const float second_x1 = second.get_top_left().x;
    const float second_y1 = second.get_top_left().y;
    const float second_x2 = second.get_bottom_right().x;
    const float second_y2 = second.get_bottom_right().y;

    // check if straight connection is possible
    if (first_x1 < second_x1 && first_x2 > second_x1 || first_x1 < second_x2 && first_x2 > second_x2 ||
        second_x1 < first_x1 && second_x2 > first_x1 || second_x1 < first_x2 && second_x2 > first_x2) {
        return std::min(std::abs(first_x2 - second_x1), std::abs(first_x1 - second_x2));
    } else if (first_y1 < second_y1 && first_y2 > second_y1 || first_y1 < second_y2 && first_y2 > second_y2 ||
        second_y1 < first_y1 && second_y2 > first_y1 || second_y1 < first_y2 && second_y2 > first_y2) {
        return std::min(std::abs(first_y2 - second_y1), std::abs(first_y1 - second_y2));
    }

    // otherwise return closest distance between any bbox points
    const Point first_bbox_points[] = {first.get_top_left(), first.get_top_right(), first.get_bottom_left(), first.get_bottom_right()};
    const Point second_bbox_points[] = {second.get_top_left(), second.get_top_right(), second.get_bottom_left(), second.get_bottom_right()};

    int minimal_distance = Point::manhattan_distance(first_bbox_points[0], second_bbox_points[0]);

    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            int distance = Point::manhattan_distance(first_bbox_points[i], second_bbox_points[j]);
            minimal_distance = std::min(minimal_distance, distance);
        }
    }

    return minimal_distance;
}
