#pragma once

#include <ostream>

struct Point {
    float x;
    float y;

    Point(float x, float y)
            : x(x),
              y(y) {}

    [[nodiscard]] Point shifted_by(float offset_x, float offset_y) const;

    bool operator==(const Point& other) const = default;

    friend std::ostream &operator<<(std::ostream &stream, const Point& point);
};
