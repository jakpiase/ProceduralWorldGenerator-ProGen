#pragma once

#include <vector>
#include <entt/entity/registry.hpp>
#include "core/Scene.h"

class Entity {

private:
    Scene &scene;
    entt::entity handle;

public:
    Entity(Scene &scene);

    template<typename T, typename... Args>
    T &add_component(Args &&... args) {
        return scene.get_registry().emplace<T>(handle, std::forward<Args>(args)...);
    }
};


