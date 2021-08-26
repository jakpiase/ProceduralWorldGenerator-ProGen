#pragma once
#include "src/pcg/generator.h"
#include "src/core/common/bounding_box.h"

class SimpleRoomGenerator : public Generator {
private:
    const BoundingBox& bounding_box;

public:
    explicit SimpleRoomGenerator(const BoundingBox& boundingBox)
            : bounding_box(boundingBox) {}

    void run(Scene &scene) override;
};
