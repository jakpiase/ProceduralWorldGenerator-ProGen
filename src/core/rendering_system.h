#include <entt/entity/registry.hpp>
#include <entt/locator/locator.hpp>
#include "src/core/components/transformation_component.h"
#include "src/core/components/graphics_component.h"
#include "src/core/entity_system.h"
#include "src/graphics/renderer.h"

class RenderingSystem : public EntitySystem {
private:
    entt::registry& registry;
    std::shared_ptr<Renderer> renderer;

public:
    explicit RenderingSystem(entt::registry& registry)
        :   registry(registry),
            renderer(entt::service_locator<Renderer>::get().lock()) {}

    void update() override;

private:
    void render_entity(const TransformationComponent& transformation, const GraphicsComponent& graphics);

};



