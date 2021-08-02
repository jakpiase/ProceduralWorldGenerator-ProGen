#pragma once

#include "src/pcg/generator.h"
#include "src/core/common/bounding_box.h"

class SimpleRoomGenerator : public Generator {
private:
    const BoundingBox &boundingBox;

public:
    explicit SimpleRoomGenerator(const BoundingBox &boundingBox)
            : boundingBox(boundingBox) {}

    void run(Scene &scene) override;
};
