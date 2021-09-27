#pragma once

#include <memory>
#include "src/core/common/bounding_box.h"

enum class GridElement {
    NONE,
    ROOM,
    CORRIDOR
};

class Grid {
    const size_t width;
    const size_t height;
    std::unique_ptr<GridElement[]> array;

public:
    Grid(size_t width, size_t height);

    GridElement& operator()(size_t row, size_t column);

    const GridElement& operator()(size_t row, size_t column) const;

    void fill(const BoundingBox2i& box, GridElement element);

    [[nodiscard]] size_t get_width() const;

    [[nodiscard]] size_t get_height() const;

private:
    [[nodiscard]] size_t get_index(size_t row, size_t column) const;
};


