#include "Scene.h"
#include "Entity.h"
#include "DescribingSystem.h"

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
    for (std::unique_ptr<EntitySystem> &system : systems) {
        system->update();
    }
}

