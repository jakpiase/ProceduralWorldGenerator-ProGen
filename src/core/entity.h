#pragma once
#include <vector>
#include <entt/entity/registry.hpp>
#include <glog/logging.h>
#include "src/core/scene.h"

class Entity {

private:
    Scene &scene;
    entt::entity handle;

public:
    Entity(Scene &scene);

    template<typename T, typename... Args>
    T &add_component(Args &&... args) {
        DLOG(INFO) << "Adding component type " << typeid(T).name() << " to entity with handle " << static_cast<int>(handle);

        return scene.get_registry().emplace<T>(handle, std::forward<Args>(args)...);
    }
};


