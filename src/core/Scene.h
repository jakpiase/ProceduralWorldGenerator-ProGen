#pragma once
#include <vector>
#include <memory>
#include <entt/entity/registry.hpp>

class Entity;

class Scene {

private:
    entt::registry registry;

public:
    entt::registry& get_registry();
    Entity create_entity();
};



