#pragma once

#include <entt/entity/registry.hpp>
#include "src/core/entity_system.h"

class DescribingSystem : public EntitySystem {

private:
    entt::registry &registry;

public:

    explicit DescribingSystem(entt::registry &registry)
            : registry(registry) {}

    void update();
};



