#include <gtest/gtest.h>
#include "src/pcg/utils/grid_to_entity_parser.h"

TEST(Grid_to_entity_parser, should_parse_entities_properly){
    Grid grid(10, 10);

    grid.fill(BoundingBox2i(Point2i(3, 2), Point2i(7, 5)), GridElement::ROOM);
    grid.fill(BoundingBox2i(Point2i(6,1), Point2i(7,7)), GridElement::ROOM);
    grid.fill(BoundingBox2i(Point2i(4,6), Point2i(5, 8)), GridElement::CORRIDOR);

    GridToEntityParser
}
