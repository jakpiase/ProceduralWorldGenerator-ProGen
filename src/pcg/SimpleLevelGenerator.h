#pragma once

#include "Generator.h"
#include "../core/common/BoundingBox.h"


class SimpleLevelGenerator : public Generator {
private:
    const BoundingBox& bounding_box;

public:
    explicit SimpleLevelGenerator(const BoundingBox& bounding_box)
            : bounding_box(bounding_box) {}

    void run(Scene &scene) override;
};



