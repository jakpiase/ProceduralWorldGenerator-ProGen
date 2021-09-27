#include <gtest/gtest.h>
#include "src/pcg/grid.h"

const size_t WIDTH = 10;
const size_t HEIGHT = 10;

TEST(Grid_test, should_be_empty_at_start) {
    Grid grid(WIDTH, HEIGHT);

    for (int row = 0; row < HEIGHT; row++) {
        for (int column = 0; column < WIDTH; column++) {
            ASSERT_EQ(grid(row, column), GridElement::NONE);
        }
    }
}

TEST(Grid_test, should_properly_store_data) {
    Grid grid(WIDTH, HEIGHT);

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = i % 2; j < WIDTH; j += 2) {
            grid(i, j) = GridElement::ROOM;
        }
    }

    for (int row = 0; row < HEIGHT; row++) {
        for (int column = 0; column < WIDTH; column++) {
            if ((row + column) % 2 == 0) {
                ASSERT_EQ(grid(row, column), GridElement::ROOM);
            } else {
                ASSERT_EQ(grid(row, column), GridElement::NONE);
            }
        }
    }
}

TEST(Grid_test, fill_method_test) {
    Grid grid(WIDTH, HEIGHT);

    grid.fill(BoundingBox2i(Point(1, 2), Point(5, 6)), GridElement::ROOM);

    for (int row = 0; row < WIDTH; row++) {
        for (int column = 0; column < WIDTH; column++) {
            if (column >= 1 && column <= 5 && row >= 2 && row <= 6) {
                ASSERT_EQ(grid(row, column), GridElement::ROOM);
            } else {
                ASSERT_EQ(grid(row, column), GridElement::NONE);
            }
        }
    }
}
