#pragma once

#include <string>
#include "src/core/common/bounding_box.h"

struct PhysicsComponent {
    Dimensions2i dimensions;

    PhysicsComponent() = default;

    PhysicsComponent(const PhysicsComponent& physics_component) = default;

    explicit PhysicsComponent(const BoundingBox2i& bounding_box)
            : dimensions(bounding_box.get_width(), bounding_box.get_height()) {}

    explicit PhysicsComponent(const Dimensions2i& dimensions)
            : dimensions(dimensions) {}
};
