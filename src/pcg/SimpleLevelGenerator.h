#pragma once

#include "Generator.h"
#include "core/common/BoundingBox.h"


class SimpleLevelGenerator : public Generator {
private:
    const BoundingBox &boundingBox;

public:
    explicit SimpleLevelGenerator(const BoundingBox &boundingBox)
            : boundingBox(boundingBox) {}

    void run(Scene &scene) override;
};



