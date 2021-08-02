#include "src/core/scene.h"
#include "src/core/entity.h"
#include "src/core/describing_system.h"

Scene::Scene() {
    systems.push_back(std::make_unique<DescribingSystem>(registry));
}

entt::registry &Scene::get_registry() {
    return registry;
}

Entity Scene::create_entity() {
    return Entity(*this);
}

void Scene::update() {
    DLOG(INFO) << "Updating scene at address" << this;
    for (std::unique_ptr<EntitySystem> &system : systems) {
        system->update();
    }
}

