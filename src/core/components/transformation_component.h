#pragma once
#include "src/core/common/point.h"

struct TransformationComponent {
    Point position;

    TransformationComponent() = default;

    TransformationComponent(const TransformationComponent &) = default;

    explicit TransformationComponent(const Point& position)
            : position(position) {}

};



