#include "BoundingBox.h"

BoundingBox::BoundingBox(Point topLeft, Point bottomRight)
        : topLeft(topLeft),
          bottomRight(bottomRight) {}

BoundingBox BoundingBox::fromZero(float width, float height) {
    return BoundingBox(Point(0, 0), Point(width, height));
}

Point BoundingBox::getBottomLeft() const {
    return Point(topLeft.x, bottomRight.y);
}

Point BoundingBox::getTopLeft() const {
    return topLeft;
}

Point BoundingBox::getBottomRight() const {
    return bottomRight;
}

Point BoundingBox::getTopRight() const {
    return Point(bottomRight.x, topLeft.y);
}

float BoundingBox::getWidth() const {
    return bottomRight.x - topLeft.x;
}

float BoundingBox::getHeight() const {
    return topLeft.y - bottomRight.y;
}

Point BoundingBox::getMiddle() const {
    const float x = (topLeft.x + bottomRight.x) / 2.0f;
    const float y = (topLeft.y + bottomRight.y) / 2.0f;
    return Point(x, y);
}
