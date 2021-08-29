#pragma once

#include <string>
#include "src/core/common/bounding_box.h"

struct PhysicsComponent {
    BoundingBox bounding_box;

    PhysicsComponent() = default;

    PhysicsComponent(const PhysicsComponent& physics_component) = default;

    explicit PhysicsComponent(const BoundingBox bounding_box)
            : bounding_box(bounding_box) {}

};
