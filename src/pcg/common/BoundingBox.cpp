#include "BoundingBox.h"

BoundingBox::BoundingBox(Point topLeft, Point bottomRight)
        : topLeft(topLeft),
          bottomRight(bottomRight) {}

BoundingBox BoundingBox::fromZero(float width, float height) {
    return BoundingBox(Point(0, 0), Point(width, height));
}
