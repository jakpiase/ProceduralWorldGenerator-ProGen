#pragma once
#include <glog/logging.h>
#include "rendering_system.h"
#include "src/core/components/transformation_component.h"
#include "src/core/components/graphics_component.h"

void RenderingSystem::update() {
    DLOG(INFO) << "Rendering system update running";

    auto view = registry.view<TransformationComponent, GraphicsComponent>();

    for (auto entity : view) {
        TransformationComponent &transformation_component = view.get<TransformationComponent>(entity);
        GraphicsComponent &graphics_component = view.get<GraphicsComponent>(entity);

        render_entity(transformation_component, graphics_component);
    }
}

void RenderingSystem::render_entity(TransformationComponent& transformation, GraphicsComponent& graphics) {
    BoundingBox box = BoundingBox::from_dimensions(transformation.position, graphics.dimensions.cast<float>());
    if(graphics.texture){
        renderer->render(*graphics.texture, box);
    } else {
        renderer->render(graphics.color, box);
    }
}

