#pragma once
#include "src/core/common/point.h"

struct TransformationComponent {
    Point2f position;

    TransformationComponent() = default;

    TransformationComponent(const TransformationComponent &) = default;

    explicit TransformationComponent(const Point2f& position)
            : position(position) {}

};



