#pragma once

#include "Generator.h"
#include "core/common/BoundingBox.h"

class SimpleRoomGenerator : public Generator {
private:
    const BoundingBox &boundingBox;

public:
    explicit SimpleRoomGenerator(const BoundingBox &boundingBox)
            : boundingBox(boundingBox) {}

    void run(Scene &scene) override;
};
