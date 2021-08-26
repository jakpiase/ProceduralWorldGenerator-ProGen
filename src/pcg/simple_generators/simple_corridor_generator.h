#pragma once
#include "src/pcg/generator.h"
#include "src/core/common/bounding_box.h"

enum class SimpleCorridorAlignment{
    Horizontal,
    Vertical,
};

class SimpleCorridorGenerator : public Generator {
private:
    const BoundingBox& bounding_box;
    const SimpleCorridorAlignment alignment;

    static inline const float CORRIDOR_WIDTH = 10.0;

public:
    SimpleCorridorGenerator(const BoundingBox& bounding_box, SimpleCorridorAlignment alignment)
        :   bounding_box(bounding_box),
            alignment(alignment) {}

    void run(Scene& scene) override;

private:
    BoundingBox create_corridor_box() const;
};



