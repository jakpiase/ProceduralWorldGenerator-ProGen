#pragma once
#include <entt/entity/registry.hpp>
#include "src/core/components/transformation_component.h"
#include "src/core/components/graphics_component.h"
#include "src/core/entity_system.h"
#include "src/io/renderer.h"
#include "src/core/locator.h"

class RenderingSystem : public EntitySystem {
private:
    entt::registry& registry;
    std::shared_ptr<Renderer> renderer;

public:
    explicit RenderingSystem(entt::registry& registry)
        :   registry(registry),
            renderer(locator::renderer) {}

    void update() override;

private:
    void render_entity(TransformationComponent& transformation, GraphicsComponent& graphics);

};



