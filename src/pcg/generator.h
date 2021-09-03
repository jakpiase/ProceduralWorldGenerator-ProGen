#pragma once

#include "src/core/common/bounding_box.h"

class Scene;

class Generator {
protected:
    const BoundingBox& bounding_box;

public:
    explicit Generator(const BoundingBox& bounding_box)
            : bounding_box(bounding_box) {};
    virtual void run(Scene& scene) = 0;
};
