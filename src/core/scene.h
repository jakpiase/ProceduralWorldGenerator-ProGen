#pragma once
#include <vector>
#include <memory>
#include <entt/entity/registry.hpp>
#include "src/graphics/renderer.h"
#include "src/core/entity_system.h"
#include "src/random/linear_number_generator.h"

class Entity;

class Scene {

private:
    entt::registry registry;
    std::vector<std::unique_ptr<EntitySystem>> systems;
    LinearNumberGenerator random_generator;

public:
    Scene(Renderer& renderer);

    entt::registry& get_registry();

    Entity create_entity();

    void update();

    LinearNumberGenerator& get_random_generator();
};



