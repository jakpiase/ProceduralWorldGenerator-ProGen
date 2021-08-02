#include "Point.h"

std::ostream& operator<<(std::ostream &stream, const Point& point) {
    return stream << "(" << point.x << ", " << point.y << ")";
}

Point Point::shifted_by(float offset_x, float offset_y) const {
    return Point(x + offset_x, y + offset_y);
}
