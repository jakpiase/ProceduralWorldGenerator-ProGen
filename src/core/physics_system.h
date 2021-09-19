#pragma once

#include <entt/entity/registry.hpp>
#include "src/core/entity_system.h"

class PhysicsSystem : public EntitySystem {

private:
    entt::registry &registry;

public:

    explicit PhysicsSystem(entt::registry &registry)
            : registry(registry) {}

    void update();
};



