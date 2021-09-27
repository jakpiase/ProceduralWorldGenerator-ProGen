#include "src/core/common/point.h"

template<typename T>
Point<T> Point<T>::shifted_by(T offset_x, T offset_y) const {
    return Point(x + offset_x, y + offset_y);
}

template<typename T>
bool Point<T>::operator==(const Point &other) const {
    return x == other.x && y == other.y;
}

template<typename T>
bool Point<T>::is_above(const Point& other) const {
    return y < other.y;
}

template<typename T>
bool Point<T>::is_on_left(const Point& other) const {
    return x < other.x;
}

template<typename T>
int Point<T>::manhattan_distance(const Point& first, const Point& second) {
    return std::abs(first.x - second.x) + std::abs(first.y - second.y);
}

template<typename T>
Point<T> Point<T>::midpoint(const Point& first, const Point& second) {
    return Point((first.x + second.x) / 2, (first.y + second.y) / 2);
}

template<typename T>
bool Point<T>::is_vertical_distance_bigger(const Point& first, const Point& second) {
    return std::abs(first.x - second.x) < std::abs(first.y - second.y);
}

template class Point<float>;
template class Point<int>;
