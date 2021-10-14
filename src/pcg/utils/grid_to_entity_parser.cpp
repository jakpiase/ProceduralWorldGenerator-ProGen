#include <glog/logging.h>
#include "src/pcg/utils/entity_creator.h"
#include "src/pcg/utils/grid_to_entity_parser.h"

GridToEntityParser::GridToEntityParser(Grid& grid, Scene& scene) : grid(grid), scene(scene) {
    const size_t size = grid.get_width() * grid.get_height();
    visits_map = std::make_unique<bool[]>(size);

    if (!visits_map) {
        LOG(ERROR) << "Could not allocate space for array of size: " << size;
    } else {
        LOG(INFO) << "Successfully created array of size: " << size;
    }
}

void GridToEntityParser::parse() {
    for (size_t row = 0; row < grid.get_height(); ++row) {
        for (size_t column = 0; column < grid.get_width(); ++column) {
            process_field(row, column);
        }
    }
}

void GridToEntityParser::process_field(size_t row, size_t column) {
    if (is_visited(row, column))
        return;

    if (grid(row, column) == GridElement::EMPTY) {
        mark_visited(row, column);
        return;
    }

    create_entity_from_grid(row, column);
}

void GridToEntityParser::create_entity_from_grid(size_t row, size_t column) {
    const BoundingBox2i box = find_entity_box(row, column);
    const GridElement element = grid(row, column);

    switch (element) {
        case GridElement::ROOM:
            return EntityCreator::create_room_floor(scene, box);
        case GridElement::CORRIDOR:
            return EntityCreator::create_corridor_floor(scene, box);
        default:
            return;
    }
}

BoundingBox2i GridToEntityParser::find_entity_box(size_t row, size_t column) {
    const GridElement element = grid(row, column);
    const size_t rect_right = traverse_horizontally(row, column, element);
    const size_t rect_bottom = traverse_vertically(row, column, rect_right, element);

    return BoundingBox2i(Point2i(row, column),
                         Point2i(rect_right, rect_bottom));
}

size_t GridToEntityParser::traverse_horizontally(size_t row, size_t column, GridElement element) {
    while (!is_visited(row, column) && grid(row, column) == element) {
        mark_visited(row, column++);
    }

    return column - 1;
}

size_t GridToEntityParser::traverse_vertically(size_t row, size_t left, size_t right, GridElement element) {
    while (can_row_be_included(row, left, right, element)) {
        mark_row_as_visited(row, left, right);
        row++;
    }

    return row - 1;
}

bool GridToEntityParser::can_row_be_included(size_t row, size_t column_from, size_t column_to, GridElement element) {
    while (column_from <= column_to) {
        if (is_visited(row, column_from) || grid(row, column_from) != element) {
            return false;
        }
        column_from++;
    }

    return true;
}

void GridToEntityParser::mark_row_as_visited(size_t row, size_t column_from, size_t column_to) {
    while (column_from <= column_to) {
        mark_visited(row, column_from++);
    }
}

bool GridToEntityParser::is_visited(size_t row, size_t column) {
    visits_map.get()[get_index(row, column)];
}

void GridToEntityParser::mark_visited(size_t row, size_t column) {
    visits_map.get()[get_index(row, column)] = true;
}

size_t GridToEntityParser::get_index(size_t row, size_t column) {
    return row * grid.get_width() + column;
}



