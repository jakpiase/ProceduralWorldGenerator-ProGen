#include "Entity.h"

Entity::Entity(Scene &scene)
        : scene(scene) {
    handle = scene.get_registry().create();
}
