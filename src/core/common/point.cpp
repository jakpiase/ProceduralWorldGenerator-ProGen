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

int Point::manhattan_distance(Point first, Point second) {
    return std::abs(first.x - second.x) + std::abs(first.y - second.y);
}
