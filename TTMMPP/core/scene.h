#pragma once

#include <vector>
#include <memory>
#include <entt/entity/registry.hpp>
#include "src/core/entity_system.h"

class Entity;

class Scene {

private:
    entt::registry registry;
    std::vector<std::unique_ptr<EntitySystem>> systems;

public:
    Scene();

    entt::registry &get_registry();

    Entity create_entity();

    void update();
};



