#include <glog/logging.h>
#include "src/core/rendering_system.h"

void RenderingSystem::update() {
    //DLOG(INFO) << "Rendering system update running";

    auto view = registry.view<TransformationComponent, GraphicsComponent>();

    for (auto entity : view) {
        TransformationComponent &transformation_component = view.get<TransformationComponent>(entity);
        GraphicsComponent &graphics_component = view.get<GraphicsComponent>(entity);

        render_entity(transformation_component, graphics_component);
    }
}

void RenderingSystem::render_entity(const TransformationComponent& transformation, const GraphicsComponent& graphics) {
    BoundingBox2i box = BoundingBox2i::from_dimensions(transformation.position, graphics.dimensions);
    if(graphics.texture){
        renderer->render(*graphics.texture, box);
    } else {
        renderer->render(graphics.color, box);
    }
}

