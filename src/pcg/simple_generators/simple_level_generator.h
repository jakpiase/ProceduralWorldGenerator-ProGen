#pragma once

#include "src/pcg/generator.h"

class SimpleLevelGenerator : public Generator {
public:
    explicit SimpleLevelGenerator(const BoundingBox2f& bounding_box)
            : Generator(bounding_box) {}

    void run(Scene& scene) override;
};



