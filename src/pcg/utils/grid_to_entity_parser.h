#pragma once
#include "src/pcg/grid.h"
#include "src/core/scene.h"
#include "src/pcg/utils/entity_creator.h"

class GridToEntityParser {
    const Grid& grid;
    Scene& scene;
    EntityCreator& entity_creator;

    std::unique_ptr<bool[]> visits_map;

public:
    GridToEntityParser(Grid& grid, Scene& scene);

    void parse();

private:

    void process_field(size_t row, size_t column);

    BoundingBox2i find_entity_box(size_t row, size_t column);

    void create_entity_from_grid(size_t row, size_t column);

    size_t traverse_horizontally(size_t row, size_t column, GridElement element);

    size_t traverse_vertically(size_t row, size_t left, size_t right, GridElement element);

    bool can_row_be_included(size_t row, size_t column_from, size_t column_to, GridElement element);

    void mark_row_as_visited(size_t row, size_t column_from, size_t column_to);

    bool is_visited(size_t row, size_t column);

    void mark_visited(size_t row, size_t column);

    size_t get_index(size_t row, size_t column);

};
