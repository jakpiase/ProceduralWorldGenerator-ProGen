#pragma once

#include <vector>
#include <memory>
#include <iostream>
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

    class Iterator;

    Grid(size_t width, size_t height);

    GridElement& operator()(size_t row, size_t column);

    const GridElement& operator()(size_t row, size_t column) const;

    const GridElement& operator()(Point2i point) const;

    void fill(const BoundingBox2i& box, GridElement element);

    void fill_no_override(const BoundingBox2i& box, GridElement element);

    [[nodiscard]] std::vector<GridElement> get_neumann_neighbourhood(size_t row, size_t column) const;

    [[nodiscard]] bool contains(Point2i& position) const;

    [[nodiscard]] bool contains(const BoundingBox2i& box) const;

    [[nodiscard]] size_t get_width() const;

    [[nodiscard]] size_t get_height() const;

    [[nodiscard]] BoundingBox2i get_bounding_box() const;

    Iterator begin(const BoundingBox2i& box);

    Iterator end(const BoundingBox2i& box);

    friend std::ostream& operator<<(std::ostream& stream, const Grid& grid);

    class Iterator {
        friend class Grid;

    private:
        Grid* grid;
        BoundingBox2i box;
        size_t row;
        size_t column;

    public:
        using difference_type   = std::ptrdiff_t;
        using value_type        = GridElement;
        using pointer           = GridElement*;
        using reference         = GridElement&;

        Iterator() = default;

        reference operator*() const;

        pointer operator->();

        Iterator& operator++();

        Iterator operator++(int);

        bool operator==(const Iterator& other) const;

        bool operator!=(const Iterator& other) const;


    private:
        Iterator(Grid& grid, const BoundingBox2i& box, bool is_begin);

        void increment();
    };

private:
    [[nodiscard]] size_t get_index(size_t row, size_t column) const;
};
