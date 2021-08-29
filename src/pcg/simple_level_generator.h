#pragma once

#include "src/pcg/space_generator.h"

class SimpleLevelGenerator : public SpaceGenerator {
public:
    explicit SimpleLevelGenerator(const BoundingBox& bounding_box)
            : SpaceGenerator(bounding_box) {}

    void run(Scene &scene) override;
};



