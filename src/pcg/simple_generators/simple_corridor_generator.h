#pragma once
#include "src/pcg/generator.h"
#include "src/core/common/bounding_box.h"

enum class SimpleCorridorAlignment{
    Horizontal,
    Vertical,
};

class SimpleCorridorGenerator : public Generator {
    const SimpleCorridorAlignment alignment;
    static constexpr float CORRIDOR_WIDTH = 10.0;

public:
    SimpleCorridorGenerator(const BoundingBox2f& bounding_box, SimpleCorridorAlignment alignment)
        : Generator(bounding_box), alignment(alignment) {};

    void run(Scene& scene) override;

private:
    [[nodiscard]] BoundingBox2f create_corridor_box() const;
};



