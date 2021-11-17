#include <glog/logging.h>
#include <algorithm>
#include <cassert>
#include "src/pcg/grid.h"

Grid::Grid(size_t width, size_t height)
        : width(width), height(height) {
    const size_t size = width * height;
    array = std::make_unique<GridElement[]>(size);
    if (!array) {
        LOG(ERROR) << "Could not allocate space for grid of size: " << width << " x " << height;
    } else {
        LOG(INFO) << "Successfully created grid of size: " << width << " x " << height;
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

void Grid::fill_no_override(const BoundingBox2i& box, GridElement element) {
    std::ranges::for_each(begin(box), end(box), [element](GridElement& current_element) {
        if (current_element == GridElement::EMPTY)
            current_element = element;
    });
}

bool Grid::contains(const BoundingBox2i& box) const {
    return get_bounding_box().contains(box);
}

GridElement& Grid::operator()(size_t row, size_t column) {
    return array[get_index(row, column)];
}

const GridElement& Grid::operator()(size_t row, size_t column) const {
    return array[get_index(row, column)];
}

size_t Grid::get_index(size_t row, size_t column) const {
    assert((row < height && column < width));

    return row * width + column;
}

size_t Grid::get_width() const {
    return width;
}

size_t Grid::get_height() const {
    return height;
}

Grid::Iterator Grid::begin(const BoundingBox2i& box) {
    return Iterator(*this, box, true);
}

Grid::Iterator Grid::end(const BoundingBox2i& box) {
    return Iterator(*this, box, false);
}

BoundingBox2i Grid::get_bounding_box() const {
    return BoundingBox2i::from_zero(width - 1, height - 1);
}

std::ostream& operator<<(std::ostream& stream, const Grid& grid) {
//    stream << '\n';
//    for(int i = 0; i<grid.height; i++){
//        for(int j = 0; j< grid.width; j++){
//            stream << static_cast<int>((grid(i, j)));
//        }
//        stream << '\n';
//    }
    return stream;
}

std::vector<GridElement> Grid::get_neumann_neighbourhood(size_t row, size_t column) const {
    std::vector<GridElement> neighbourhood;
    neighbourhood.reserve(4);

    if(row > 0) neighbourhood.push_back(this->operator()(row - 1, column));
    if(row < height - 1) neighbourhood.push_back(this->operator()(row + 1, column));
    if(column > 0) neighbourhood.push_back(this->operator()(row, column - 1));
    if(row < width - 1) neighbourhood.push_back(this->operator()(row, column + 1));

    return neighbourhood;
}

Grid::Iterator::Iterator(Grid& grid, const BoundingBox2i& box, bool is_begin)
        : grid(&grid),
          box(box),
          row(is_begin ? box.get_top() : box.get_bottom() + 1),
          column(box.get_left()) {}

GridElement* Grid::Iterator::operator->() {
    return &(*grid)(row, column);
}

GridElement& Grid::Iterator::operator*() const {
    return grid->operator()(row, column);
}

Grid::Iterator Grid::Iterator::operator++(int) {
    Iterator result = *this;
    increment();
    return result;
}

Grid::Iterator& Grid::Iterator::operator++() {
    increment();
    return *this;
}

bool Grid::Iterator::operator!=(const Grid::Iterator& other) const {
    return !(*this == other);
}

bool Grid::Iterator::operator==(const Grid::Iterator& other) const {
    return row == other.row && column == other.column;
}

void Grid::Iterator::increment() {
    if (++column > box.get_right()) {
        column = box.get_left();
        ++row;
    }
}

