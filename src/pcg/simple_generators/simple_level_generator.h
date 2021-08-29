#pragma once

#include "src/pcg/generator.h"

class SimpleLevelGenerator : public Generator {
private:
    const BoundingBox& bounding_box;

public:
    explicit SimpleLevelGenerator(const BoundingBox& bounding_box)
            : Generator(bounding_box) {}

    void run(Scene& scene) override;
};



