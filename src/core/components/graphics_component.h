#pragma once
#include <memory>
#include "src/core/common/bounding_box.h"
#include "src/graphics/color.h"
#include "src/core/common/dimensions.h"
#include "src/graphics/texture.h"

struct GraphicsComponent {
    std::shared_ptr<Texture> texture;
    Color color;
    Dimensions2i dimensions;

    GraphicsComponent() = default;

    GraphicsComponent(const GraphicsComponent &) = default;

    GraphicsComponent(std::shared_ptr<Texture> &texture, const Dimensions2i &dimensions)
            : texture(texture),
              dimensions(dimensions) {}

    GraphicsComponent(const Color& color, const Dimensions2i &dimensions)
            : color(color),
              dimensions(dimensions) {}
};


