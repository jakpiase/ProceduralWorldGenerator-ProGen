#include "src/core/common/point.h"

std::ostream& operator<<(std::ostream &stream, const Point& point) {
    return stream << "(" << point.x << ", " << point.y << ")";
}

Point Point::shifted_by(float offset_x, float offset_y) const {
    return Point(x + offset_x, y + offset_y);
}

bool Point::operator==(const Point &other) const {
    return x == other.x && y == other.y;
}

bool Point::is_above(const Point& other) const {
    return y < other.y;
}

bool Point::is_on_left(const Point& other) const {
    return x < other.x;
}

int Point::manhattan_distance(const Point& first, const Point& second) {
    return std::abs(first.x - second.x) + std::abs(first.y - second.y);
}

Point Point::midpoint(const Point& first, const Point& second) {
    return Point((first.x + second.x) / 2, (first.y + second.y) / 2);
}

bool Point::is_vertical_distance_bigger(const Point& first, const Point& second) {
    return std::abs(first.x - second.x) < std::abs(first.y - second.y);
}
