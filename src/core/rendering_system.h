#pragma once
#include <entt/entity/registry.hpp>
#include "src/core/components/transformation_component.h"
#include "src/core/components/graphics_component.h"
#include "src/core/entity_system.h"
#include "src/graphics/renderer.h"

class RenderingSystem : public EntitySystem {
private:
    entt::registry& registry;
    Renderer& renderer;

public:
    explicit RenderingSystem(entt::registry& registry, Renderer& renderer)
        :   registry(registry),
            renderer(renderer) {}

    void update() override;

private:
    void render_entity(const TransformationComponent& transformation, const GraphicsComponent& graphics);

};



