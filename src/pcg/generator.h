#pragma once

#include "src/core/common/bounding_box.h"

class Scene;

class Generator {
protected:
    const BoundingBox& bounding_box;

public:
    virtual void run(Scene& scene) = 0;
};
