#include <cassert>
#include "src/core/common/bounding_box.h"

template<typename T>
BoundingBox<T>::BoundingBox(Point<T> top_left, Point<T> bottom_right)
        : top_left(top_left),
          bottom_right(bottom_right) {}

template<typename T>
BoundingBox<T>::BoundingBox(Point<T> position, Dimensions<T> dimensions)
        : top_left(position),
          bottom_right(Point<T>(position.x + dimensions.width, position.y + dimensions.height)) {}

template<typename T>
BoundingBox<T> BoundingBox<T>::from_zero(T width, T height) {
    return BoundingBox(Point<T>(0, 0), Point<T>(width, height));
}

template<typename T>
BoundingBox<T> BoundingBox<T>::from_dimensions(Point<T> top_left, Dimensions<T> dimensions) {
    return BoundingBox(top_left, top_left.shifted_by(dimensions.width, dimensions.height));
}

template<typename T>
BoundingBox<T> BoundingBox<T>::from_dimensions_centered(Point<T> center, Dimensions<T> dimensions) {
    return BoundingBox::from_dimensions(center.shifted_by(-dimensions.width / 2,
                                                          -dimensions.height / 2),
                                        dimensions);
}

template<typename T>
Point<T> BoundingBox<T>::get_bottom_left() const {
    return Point<T>(top_left.x, bottom_right.y);
}

template<typename T>
Point<T> BoundingBox<T>::get_top_left() const {
    return top_left;
}

template<typename T>
Point<T> BoundingBox<T>::get_bottom_right() const {
    return bottom_right;
}

template<typename T>
Point<T> BoundingBox<T>::get_top_right() const {
    return Point<T>(bottom_right.x, top_left.y);
}

template<typename T>
T BoundingBox<T>::get_width() const {
    return bottom_right.x - top_left.x;
}

template<typename T>
T BoundingBox<T>::get_height() const {
    return bottom_right.y - top_left.y;
}

template<typename T>
Point<T> BoundingBox<T>::get_middle() const {
    const T x = (top_left.x + bottom_right.x) / static_cast<T>(2);
    const T y = (top_left.y + bottom_right.y) / static_cast<T>(2);
    return Point<T>(x, y);
}

template<typename T>
Dimensions<T> BoundingBox<T>::get_dimensions() const {
    return Dimensions<T>(get_width(), get_height());
}

template<typename T>
T BoundingBox<T>::get_top() const {
    return get_top_left().y;
}

template<typename T>
T BoundingBox<T>::get_bottom() const {
    return get_bottom_right().y;
}

template<typename T>
T BoundingBox<T>::get_left() const {
    return get_top_left().x;
}

template<typename T>
T BoundingBox<T>::get_right() const {
    return get_top_right().x;
}

template<typename T>
bool BoundingBox<T>::collides_with(const BoundingBox<T>& other) const {

    return get_left() <= other.get_right() &&
           get_right() >= other.get_left() &&
           get_top() <= other.get_bottom() &&
           get_bottom() >= other.get_top();
//    if (get_top_left().x == get_bottom_right().x ||
//        get_top_left().y == get_bottom_right().y ||
//        other.get_top_left().x == other.get_bottom_right().x ||
//        other.get_top_left().y == other.get_bottom_right().y)
//        return false;
//
//    return !(get_top_left().x > other.get_bottom_right().x ||
//             other.get_top_left().x > get_bottom_right().x ||
//             get_top_left().y > other.get_bottom_right().y ||
//             other.get_top_left().y > get_bottom_right().y);
}

template<typename T>
int BoundingBox<T>::manhattan_distance(const BoundingBox& first, const BoundingBox& second) {
    const T first_x1 = first.get_top_left().x;
    const T first_y1 = first.get_top_left().y;
    const T first_x2 = first.get_bottom_right().x;
    const T first_y2 = first.get_bottom_right().y;

    const T second_x1 = second.get_top_left().x;
    const T second_y1 = second.get_top_left().y;
    const T second_x2 = second.get_bottom_right().x;
    const T second_y2 = second.get_bottom_right().y;

    // check if straight connection is possible
    if (first_x1 < second_x1 && first_x2 > second_x1 || first_x1 < second_x2 && first_x2 > second_x2 ||
        second_x1 < first_x1 && second_x2 > first_x1 || second_x1 < first_x2 && second_x2 > first_x2) {
        return std::min(std::abs(first_x2 - second_x1), std::abs(first_x1 - second_x2));
    } else if (first_y1 < second_y1 && first_y2 > second_y1 || first_y1 < second_y2 && first_y2 > second_y2 ||
               second_y1 < first_y1 && second_y2 > first_y1 || second_y1 < first_y2 && second_y2 > first_y2) {
        return std::min(std::abs(first_y2 - second_y1), std::abs(first_y1 - second_y2));
    }

    // otherwise return closest distance between any bbox Point<T>s
    const Point<T> first_bbox_points[] = {first.get_top_left(), first.get_top_right(), first.get_bottom_left(),
                                          first.get_bottom_right()};
    const Point<T> second_bbox_points[] = {second.get_top_left(), second.get_top_right(), second.get_bottom_left(),
                                           second.get_bottom_right()};

    int minimal_distance = Point<T>::manhattan_distance(first_bbox_points[0], second_bbox_points[0]);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int distance = Point<T>::manhattan_distance(first_bbox_points[i], second_bbox_points[j]);
            minimal_distance = std::min(minimal_distance, distance);
        }
    }

    return minimal_distance;
}

template<typename T>
BoundingBox<T> BoundingBox<T>::grown_by(T value) const {
    return BoundingBox(get_top_left().shifted_by(-value, -value),
                       get_bottom_right().shifted_by(value, value));
}

template<typename T>
BoundingBox<T> BoundingBox<T>::shrunk_by(T value) const {
    assert((get_width() >= 2 * value && get_height() >= 2 * value));

    return BoundingBox(get_top_left().shifted_by(value, value),
                       get_bottom_right().shifted_by(-value, -value));
}

template<typename T>
bool BoundingBox<T>::contains(const Point<T>& point) const {
    return point.x >= get_left() && point.x <= get_right() && point.y >= get_top() && point.y <= get_bottom();
}

template<typename T>
bool BoundingBox<T>::contains(const BoundingBox& other) const {
    return get_left() <= other.get_left() &&
           get_right() >= other.get_right() &&
           get_top() <= other.get_top() &&
           get_bottom() >= other.get_bottom();
}

template<typename T>
bool BoundingBox<T>::operator==(const BoundingBox& other) const {
    return top_left == other.top_left && bottom_right == other.bottom_right;
}

template<typename T>
BoundingBox<T> BoundingBox<T>::common_part_with(const BoundingBox& other) const {
    assert((collides_with(other))); //Unforseen use case

    const T left = std::max(get_left(), other.get_left());
    const T right = std::min(get_right(), other.get_right());
    const T top = std::max(get_top(), other.get_top());
    const T bottom = std::min(get_bottom(), other.get_bottom());

    return {Point(left, top), Point(right, bottom)};
}


template
class BoundingBox<float>;

template
class BoundingBox<int>;
