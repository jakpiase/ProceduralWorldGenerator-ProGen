#pragma once
#include "src/core/scene.h"
#include "src/core/entity.h"
#include "src/core/describing_system.h"
#include "src/core/physics_system.h"
#include "src/core/rendering_system.h"

Scene::Scene() {
    systems.push_back(std::make_unique<DescribingSystem>(registry));
    systems.push_back(std::make_unique<PhysicsSystem>(registry));
    systems.push_back(std::make_unique<RenderingSystem>(registry));
}

entt::registry &Scene::get_registry() {
    return registry;
}

Entity Scene::create_entity() {
    return Entity(*this);
}

void Scene::update() {
    //DLOG(INFO) << "Updating scene at address " << this;
    for (std::unique_ptr<EntitySystem> &system : systems) {
        system->update();
    }
}
