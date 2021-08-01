#pragma once

#include <ostream>

struct Point {
    float x;
    float y;

    Point(float x, float y)
        : x(x),
          y(y) {}

    [[nodiscard]] Point move(float offset_x, float offset_y) const;

    std::ostream& operator<<(std::ostream& stream) const;
};
