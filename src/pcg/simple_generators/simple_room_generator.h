#pragma once

#include "src/core/scene.h"
#include "src/core/entity.h"
#include "src/core/components/graphics_component.h"
#include "src/core/components/description_component.h"
#include "src/core/components/transformation_component.h"
#include "src/core/components/physics_component.h"
#include "src/pcg/generator.h"

class SimpleRoomGenerator : public Generator {
public:
    explicit SimpleRoomGenerator(const BoundingBox2i &bounding_box)
            : Generator(bounding_box) {}

    void run(Scene &scene) override;
};
