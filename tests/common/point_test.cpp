#include "gtest/gtest.h"
#include "src/core/common/bounding_box.h"

TEST(Point_test, shifting_test) {
    Point point(21, 37);

    Point shifted_point = point.shifted_by(4, 20);

    ASSERT_EQ(shifted_point, Point(25, 57));
}
