#include <glog/logging.h>
#include "src/pcg/grid.h"

Grid::Grid(size_t width, size_t height)
        : width(width), height(height) {
    const size_t size = width * height;
    array = std::make_unique<GridElement[]>(size);
    if (!array) {
        LOG(ERROR) << "Could not allocate space for grid of size: " << width << " x " << height;
    }

    std::fill(array.get(), array.get() + size, GridElement::EMPTY);
}

void Grid::fill(const BoundingBox2i& box, GridElement element) {
    for (int row = box.get_top(); row <= box.get_bottom(); ++row) {
        for (int column = box.get_left(); column <= box.get_right(); ++column) {
            this->operator()(row, column) = element;
        }
    }
}

GridElement& Grid::operator()(size_t row, size_t column) {
    return array[get_index(row, column)];
}

const GridElement& Grid::operator()(size_t row, size_t column) const {
    return array[get_index(row, column)];
}

size_t Grid::get_index(size_t row, size_t column) const {
    return row * height + column;
}

size_t Grid::get_width() const {
    return width;
}

size_t Grid::get_height() const {
    return height;
}



