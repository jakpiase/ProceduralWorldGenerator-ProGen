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
