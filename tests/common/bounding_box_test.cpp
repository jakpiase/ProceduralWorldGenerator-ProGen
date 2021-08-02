#include <src/core/common/BoundingBox.h>
#include "gtest/gtest.h"

TEST(Bounding_box_test, simple_getters_test) {
    BoundingBox box(Point(1, 2), Point(3, 4));

    ASSERT_EQ(box.get_top_left(), Point(1, 2));
    ASSERT_EQ(box.get_top_right(), Point(3, 2));
    ASSERT_EQ(box.get_bottom_right(), Point(3, 4));
    ASSERT_EQ(box.get_bottom_left(), Point(1, 4));

    ASSERT_EQ(box.get_width(), 2);
    ASSERT_EQ(box.get_height(), 2);
    ASSERT_EQ(box.get_middle(), Point(2, 3));
}
