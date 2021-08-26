#pragma once
#include "src/pcg/generator.h"
#include "src/core/common/bounding_box.h"


class SimpleLevelGenerator : public Generator {
private:
    const BoundingBox& bounding_box;

public:
    explicit SimpleLevelGenerator(const BoundingBox& bounding_box)
            : bounding_box(bounding_box) {}

    void run(Scene& scene) override;
};



