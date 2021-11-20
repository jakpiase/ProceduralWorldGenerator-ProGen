#pragma once
#include <ostream>

template <typename T>
struct Point {
    T x;
    T y;

    Point() = default;

    Point(T x, T y)
            : x(x),
              y(y) {}

    [[nodiscard]] Point shifted_by(T offset_x, T offset_y) const;

    [[nodiscard]] bool operator==(const Point& other) const;

    [[nodiscard]] bool is_above(const Point& other) const;

    [[nodiscard]] bool is_on_left(const Point& other) const;

    friend std::ostream &operator<<(std::ostream &stream, const Point& point) {
        return stream << "(" << point.x << ", " << point.y << ")";
    }

    static int manhattan_distance(const Point& first, const Point& second);

    static Point midpoint(const Point& first, const Point& second);
    
    static bool is_vertical_distance_bigger(const Point& first, const Point& second);
};

typedef Point<float> Point2f;
typedef Point<int> Point2i;
