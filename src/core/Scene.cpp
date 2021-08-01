#include "Scene.h"
#include "Entity.h"

entt::registry& Scene::get_registry() {
    return registry;
}

Entity Scene::create_entity() {
    return Entity(*this);
}
