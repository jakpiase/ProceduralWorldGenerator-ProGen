#include "Entity.h"
#include "core/Scene.h"

Entity::Entity(Scene &scene)
        : scene(scene) {
    handle = scene.get_registry().create();
}
