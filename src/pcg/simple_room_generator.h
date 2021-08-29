#pragma once

#include "src/core/scene.h"
#include "src/core/entity.h"
#include "src/core/components/description_component.h"
#include "src/core/components/physics_component.h"
#include "src/pcg/space_generator.h"

class SimpleRoomGenerator : public SpaceGenerator {
public:
    explicit SimpleRoomGenerator(const BoundingBox &bounding_box)
            : SpaceGenerator(bounding_box) {}

    void run(Scene &scene) override;
};
