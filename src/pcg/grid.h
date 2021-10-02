#pragma once

#include <memory>
#include "src/core/common/bounding_box.h"

enum class GridElement {
    EMPTY,
    ROOM,
    CORRIDOR
};

class Grid {
    const size_t width;
    const size_t height;
    std::unique_ptr<GridElement[]> array;

public:
    static constexpr int ELEMENT_SIZE = 5;

    Grid(size_t width, size_t height);

    GridElement& operator()(size_t row, size_t column);

    const GridElement& operator()(size_t row, size_t column) const;

    void fill(const BoundingBox2i& box, GridElement element);

    void fill(int x, int y, int width, int height, GridElement element);

    [[nodiscard]] size_t get_width() const;

    [[nodiscard]] size_t get_height() const;

private:
    [[nodiscard]] size_t get_index(size_t row, size_t column) const;
};



