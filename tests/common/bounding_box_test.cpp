#include <gtest/gtest.h>
#include "src/core/common/bounding_box.h"

TEST(Bounding_box_test, simple_getters_test) {
    BoundingBox2i box(Point(1, 2), Point(3, 4));

    ASSERT_EQ(box.get_top_left(), Point(1, 2));
    ASSERT_EQ(box.get_top_right(), Point(3, 2));
    ASSERT_EQ(box.get_bottom_right(), Point(3, 4));
    ASSERT_EQ(box.get_bottom_left(), Point(1, 4));

    ASSERT_EQ(box.get_width(), 2);
    ASSERT_EQ(box.get_height(), 2);
    ASSERT_EQ(box.get_middle(), Point(2, 3));

    ASSERT_EQ(box.get_dimensions(), Dimensions(2, 2));
}

TEST(Bounding_box, left_top_right_bottom_getters_test) {
    BoundingBox2i box(Point2i(1, 2), Point2i(3, 4));

    ASSERT_EQ(box.get_left(), 1);
    ASSERT_EQ(box.get_top(), 2);
    ASSERT_EQ(box.get_right(), 3);
    ASSERT_EQ(box.get_bottom(), 4);
}

TEST(Bounding_box_test, from_dimensions_constructor_test) {
    BoundingBox box = BoundingBox2i::from_dimensions(Point(1, 2), Dimensions(3, 4));

    ASSERT_EQ(box.get_top_left(), Point(1, 2));
    ASSERT_EQ(box.get_bottom_right(), Point(4, 6));
}

TEST(Bounding_box_test, from_dimensions_centered_constructor_test) {
    BoundingBox box = BoundingBox2i::from_dimensions_centered(Point(3, 3), Dimensions(3, 2));

    ASSERT_EQ(box.get_top_left(), Point(2, 2));
    ASSERT_EQ(box.get_bottom_right(), Point(5, 4));
}

TEST(Bounding_box_test, from_zero_constructor_test) {
    BoundingBox box = BoundingBox2i::from_zero(6, 9);

    ASSERT_EQ(box.get_top_left(), Point(0, 0));
    ASSERT_EQ(box.get_bottom_right(), Point(6, 9));
}

TEST(Bounding_box_manhattan_distance_tests, only_vertical_distance) {
    BoundingBox2i first_box = BoundingBox(Point(100, 100), Point(200, 200));
    BoundingBox2i second_box = BoundingBox(Point(50, 250), Point(150, 350));

    ASSERT_EQ(BoundingBox2i::manhattan_distance(first_box, second_box), 50);
    ASSERT_EQ(BoundingBox2i::manhattan_distance(second_box, first_box), 50);
}

TEST(Bounding_box_manhattan_distance_tests, only_horizontal_distance) {
    BoundingBox2i first_box = BoundingBox(Point(100, 100), Point(200, 200));
    BoundingBox2i second_box = BoundingBox(Point(250, 150), Point(350, 250));

    ASSERT_EQ(BoundingBox2i::manhattan_distance(first_box, second_box), 50);
    ASSERT_EQ(BoundingBox2i::manhattan_distance(second_box, first_box), 50);
}

TEST(Bounding_box_manhattan_distance_tests, top_left_and_bottom_right_distance) {
    BoundingBox2i first_box = BoundingBox(Point(100, 100), Point(200, 200));
    BoundingBox2i second_box = BoundingBox(Point(250, 300), Point(350, 400));

    ASSERT_EQ(BoundingBox2i::manhattan_distance(first_box, second_box), 150);
    ASSERT_EQ(BoundingBox2i::manhattan_distance(second_box, first_box), 150);
}

TEST(Bounding_box_manhattan_distance_tests, top_right_and_bottom_left_distance) {
    BoundingBox2i first_box = BoundingBox(Point(250, 100), Point(350, 200));
    BoundingBox2i second_box = BoundingBox(Point(100, 450), Point(200, 550));

    ASSERT_EQ(BoundingBox2i::manhattan_distance(first_box, second_box), 300);
    ASSERT_EQ(BoundingBox2i::manhattan_distance(second_box, first_box), 300);
}

TEST(Bounding_box_collision_tests, collision) {
    BoundingBox2i first_box = BoundingBox2i(Point2i(100, 100), Point2i(200, 200));
    BoundingBox2i second_box = BoundingBox2i(Point2i(190, 190), Point2i(210, 210));

    ASSERT_TRUE(first_box.collides_with(second_box));
    ASSERT_TRUE(second_box.collides_with(first_box));
}

TEST(Bounding_box_collision_tests, no_collision) {
    BoundingBox2i first_box = BoundingBox2i(Point2i(100, 100), Point2i(200, 200));
    BoundingBox2i second_box = BoundingBox2i(Point2i(201, 201), Point2i(210, 210));

    ASSERT_FALSE(first_box.collides_with(second_box));
    ASSERT_FALSE(second_box.collides_with(first_box));
}

TEST(Bounding_box_test, grown_by) {
    BoundingBox2i box(Point(1, 2), Point(3, 4));

    BoundingBox2i grown_box = box.grown_by(1);

    ASSERT_EQ(grown_box, BoundingBox2i(Point(0, 1), Point(4, 5)));
}

TEST(Bounding_box_test, contains) {
    BoundingBox2i box(Point(1, 2), Point(6, 7));

    ASSERT_TRUE(box.contains(box));
    ASSERT_TRUE(box.contains(BoundingBox2i(Point(3, 4), Point(5, 6))));
    ASSERT_FALSE(box.contains(BoundingBox2i(Point(10, 10), Point(12, 13))));
    ASSERT_FALSE(box.contains(BoundingBox2i(Point(1, 1), Point(3, 3))));
}

TEST(Bounding_box_test, common_part_with_contained) {
    BoundingBox2i box(Point(1, 1), Point(8, 8));
    BoundingBox2i contained_box(Point(2, 3), Point(6, 7));

    BoundingBox2i common_part = box.common_part_with(contained_box);

    ASSERT_EQ(common_part, BoundingBox2i(Point(2, 3), Point(6, 7)));
}

TEST(Bounding_box_test, common_part_with_containing) {
    BoundingBox2i box(Point(2, 3), Point(6, 7));
    BoundingBox2i contained_box(Point(1, 1), Point(8, 8));

    BoundingBox2i common_part = box.common_part_with(contained_box);

    ASSERT_EQ(common_part, BoundingBox2i(Point(2, 3), Point(6, 7)));
}

TEST(Bounding_box_test, common_part_with_collider) {
    BoundingBox2i box(Point(2, 3), Point(6, 7));
    BoundingBox2i contained_box(Point(4, 5), Point(8, 9));

    BoundingBox2i common_part = box.common_part_with(contained_box);

    ASSERT_EQ(common_part, BoundingBox2i(Point(4, 5), Point(6, 7)));
}