#include "gtest/gtest.h"
#include "src/core/common/bounding_box.h"

TEST(Bounding_box_test, simple_getters_test) {
    BoundingBox box(Point(1, 2), Point(3, 4));

    ASSERT_EQ(box.get_top_left(), Point(1, 2));
    ASSERT_EQ(box.get_top_right(), Point(3, 2));
    ASSERT_EQ(box.get_bottom_right(), Point(3, 4));
    ASSERT_EQ(box.get_bottom_left(), Point(1, 4));

    ASSERT_EQ(box.get_width(), 2);
    ASSERT_EQ(box.get_height(), 2);
    ASSERT_EQ(box.get_middle(), Point(2, 3));

    ASSERT_EQ(box.get_dimensions(), Dimensions2f(2, 2));
}

TEST(Bounding_box_test, from_dimensions_constructor_test) {
    BoundingBox box = BoundingBox::from_dimensions(Point(1, 2), Dimensions2f(3, 4));

    ASSERT_EQ(box.get_top_left(), Point(1, 2));
    ASSERT_EQ(box.get_bottom_right(), Point(4, 6));
}

TEST(Bounding_box_test, from_zero_constructor_test) {
    BoundingBox box = BoundingBox::from_zero(6, 9);

    ASSERT_EQ(box.get_top_left(), Point(0, 0));
    ASSERT_EQ(box.get_bottom_right(), Point(6, 9));
}

TEST(Bounding_box_manhattan_distance_tests, only_vertical_distance) {
    BoundingBox first_box = BoundingBox(Point(100, 100), Point(200, 200));
    BoundingBox second_box = BoundingBox(Point(50, 250), Point(150, 350));

    ASSERT_EQ(BoundingBox::manhattan_distance(first_box, second_box), 50);
    ASSERT_EQ(BoundingBox::manhattan_distance(second_box, first_box), 50);
}

TEST(Bounding_box_manhattan_distance_tests, only_horizontal_distance) {
    BoundingBox first_box = BoundingBox(Point(100, 100), Point(200, 200));
    BoundingBox second_box = BoundingBox(Point(250, 150), Point(350, 250));

    ASSERT_EQ(BoundingBox::manhattan_distance(first_box, second_box), 50);
    ASSERT_EQ(BoundingBox::manhattan_distance(second_box, first_box), 50);
}

TEST(Bounding_box_manhattan_distance_tests, top_left_and_bottom_right_distance) {
    BoundingBox first_box = BoundingBox(Point(100, 100), Point(200, 200));
    BoundingBox second_box = BoundingBox(Point(250, 300), Point(350, 400));

    ASSERT_EQ(BoundingBox::manhattan_distance(first_box, second_box), 150);
    ASSERT_EQ(BoundingBox::manhattan_distance(second_box, first_box), 150);
}

TEST(Bounding_box_manhattan_distance_tests, top_right_and_bottom_left_distance) {
    BoundingBox first_box = BoundingBox(Point(250, 100), Point(350, 200));
    BoundingBox second_box = BoundingBox(Point(100, 450), Point(200, 550));

    ASSERT_EQ(BoundingBox::manhattan_distance(first_box, second_box), 300);
    ASSERT_EQ(BoundingBox::manhattan_distance(second_box, first_box), 300);
}
