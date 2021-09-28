#include <gtest/gtest.h>
#include "src/core/common/bounding_box.h"

TEST(Point_test, shifting_test) {
    Point2i point(21, 37);

    Point2i shifted_point = point.shifted_by(4, 20);

    ASSERT_EQ(shifted_point, Point2i(25, 57));
}
