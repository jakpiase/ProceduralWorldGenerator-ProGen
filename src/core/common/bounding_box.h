#pragma once

#include "src/core/common/point.h"
#include "src/core/common/dimensions.h"

template<typename T>
class BoundingBox {

private:
    Point<T> top_left;
    Point<T> bottom_right;

public:
    BoundingBox() = default;

    BoundingBox(Point<T> top_left, Point<T> bottom_right);

    BoundingBox(Point<T> position, Dimensions<T> dimensions);

    [[nodiscard]] static BoundingBox from_zero(T width, T height);

    [[nodiscard]] static BoundingBox from_dimensions(Point<T> top_left, Dimensions<T> dimensions);

    [[nodiscard]] static BoundingBox from_dimensions_centered(Point<T> center, Dimensions<T> dimensions);

    [[nodiscard]] Point<T> get_top_left() const;

    [[nodiscard]] Point<T> get_top_right() const;

    [[nodiscard]] Point<T> get_bottom_right() const;

    [[nodiscard]] Point<T> get_bottom_left() const;

    [[nodiscard]] Point<T> get_middle() const;

    [[nodiscard]] T get_width() const;

    [[nodiscard]] T get_height() const;

    [[nodiscard]] Dimensions<T> get_dimensions() const;

    [[nodiscard]] T get_top() const;

    [[nodiscard]] T get_bottom() const;

    [[nodiscard]] T get_left() const;

    [[nodiscard]] T get_right() const;

    [[nodiscard]] BoundingBox grown_by(T value) const;

    [[nodiscard]] bool contains(const BoundingBox& other) const;

    [[nodiscard]] bool contains(const Point<T>& other) const;

    [[nodiscard]] bool collides_with(const BoundingBox<T>& other) const;

    [[nodiscard]] BoundingBox common_part_with(const BoundingBox<T>& other) const;

    bool operator==(const BoundingBox& other) const;

    friend std::ostream& operator<<(std::ostream& stream, const BoundingBox& bounding_box) {
        stream << "((" << bounding_box.top_left << ") ";
        stream << "(" << bounding_box.bottom_right << "))";
        return stream;
    }

    static int manhattan_distance(const BoundingBox& first, const BoundingBox& second);
};

typedef BoundingBox<float> BoundingBox2f;
typedef BoundingBox<int> BoundingBox2i;
