#pragma once

#include <entt/entity/registry.hpp>
#include "EntitySystem.h"

class DescribingSystem : public EntitySystem {

private:
    entt::registry &registry;

public:

    explicit DescribingSystem(entt::registry &registry)
            : registry(registry) {}

    void update();
};



