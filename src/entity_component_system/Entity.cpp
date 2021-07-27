#include "Entity.h"

Entity::Entity(std::vector<Component> &components)
    : components(components) {}

template<typename T>
T* Entity::get_component() {
    for (Component& component : components) {
        if (T* casted_component = dynamic_cast<T*>(component)) {
            return casted_component;
        }
    }

    return nullptr;
}
