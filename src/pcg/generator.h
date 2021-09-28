#pragma once
#include "src/core/common/bounding_box.h"

class Scene;

class Generator {
protected:
    const BoundingBox2f& bounding_box; //FIXME: it should probably be changed to BoundingBox2i

public:
    explicit Generator(const BoundingBox2f& bounding_box)
            : bounding_box(bounding_box) {};
    
    virtual void run(Scene& scene) = 0;
};
