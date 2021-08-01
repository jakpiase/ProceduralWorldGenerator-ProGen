#include "Point.h"

std::ostream& Point::operator<<(std::ostream& stream) const {
    return stream << "(" << x << ", " << y << ")";
}

Point Point::move(float offset_x, float offset_y) const {
    return Point(x + offset_x, y + offset_y);
}
