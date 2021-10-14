#pragma once
#include "src/core/common/point.h"

struct TransformationComponent {
    Point2i position;

    TransformationComponent() = default;

    TransformationComponent(const TransformationComponent&) = default;

    explicit TransformationComponent(const Point2i& position)
            : position(position) {}

};



