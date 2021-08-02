#include "src/core/entity.h"

Entity::Entity(Scene &scene)
        : scene(scene) {
    handle = scene.get_registry().create();

    DLOG(INFO) << "Created entity with id " << static_cast<int>(handle) << " at scene address: " << &scene;
}
