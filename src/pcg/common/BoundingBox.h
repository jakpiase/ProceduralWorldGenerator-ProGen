#pragma once

#include "Point.h"

class BoundingBox {

private:
    Point topLeft;
    Point bottomRight;

public:
    BoundingBox(Point topLeft, Point bottomRight);

    [[nodiscard]] static BoundingBox fromZero(float width, float height);
};

