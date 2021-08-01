#pragma once

#include "Point.h"

class BoundingBox {

private:
    Point topLeft;
    Point bottomRight;

public:
    BoundingBox(Point topLeft, Point bottomRight);

    [[nodiscard]] static BoundingBox fromZero(float width, float height);

    [[nodiscard]] Point getTopLeft() const;

    [[nodiscard]] Point getTopRight() const;

    [[nodiscard]] Point getBottomRight() const;

    [[nodiscard]] Point getBottomLeft() const;

    [[nodiscard]] Point getMiddle() const;

    [[nodiscard]] float getWidth() const;

    [[nodiscard]] float getHeight() const;
};

