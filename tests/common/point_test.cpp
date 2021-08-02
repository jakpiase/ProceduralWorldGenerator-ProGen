#include <src/core/common/BoundingBox.h>
#include "gtest/gtest.h"

TEST(Bounding_box_test, simple_getters_test) {
    Point point(21, 37);

    Point shiftedPoint = point.shifted_by(4, 20);

    ASSERT_EQ(shiftedPoint, Point(25, 57));
}
