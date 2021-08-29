#pragma once

#include "src/pcg/generator.h"
#include "src/core/common/bounding_box.h"

class SpaceGenerator : public Generator {
protected:
    const BoundingBox& bounding_box;

public:
    explicit SpaceGenerator(const BoundingBox &bounding_box)
            : bounding_box(bounding_box) {}
};



