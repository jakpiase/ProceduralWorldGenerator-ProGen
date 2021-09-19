#pragma once
#include <ostream>

struct Point {
    float x;
    float y;

    Point(float x, float y)
            : x(x),
              y(y) {}

    [[nodiscard]] Point shifted_by(float offset_x, float offset_y) const;

    [[nodiscard]] bool operator==(const Point& other) const;

    [[nodiscard]] bool is_above(const Point& other) const;

    [[nodiscard]] bool is_on_left(const Point& other) const;

    friend std::ostream &operator<<(std::ostream &stream, const Point& point);

    static int manhattan_distance(const Point& first, const Point& second);

    static Point midpoint(const Point& first, const Point& second);
    
    static bool is_vertical_distance_bigger(const Point& first, const Point& second);
};
