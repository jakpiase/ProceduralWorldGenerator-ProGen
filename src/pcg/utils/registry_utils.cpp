#include <entt/entity/registry.hpp>
#include "src/pcg/utils/registry_utils.h"
#include "src/core/components/description_component.h"


const std::vector<entt::entity>& RegistryUtils::get_by_tag(int tag) {
    return entities_by_tag[tag];
}

void RegistryUtils::set_registry(entt::registry* registry) {
    registry_ptr = registry;
}

entt::registry& RegistryUtils::get_registry() {
    return *registry_ptr;
}

void RegistryUtils::register_entity(entt::entity entity, entt::entity room) {
    room_by_entity[entity] = room;
    entity_by_room[room].push_back(entity);

    register_entity(entity);
}

void RegistryUtils::register_entity(entt::entity entity) {
    DescriptionComponent& description_component = registry_ptr->get<DescriptionComponent>(entity);
    entities_by_tag[description_component.tag].push_back(entity);
}

std::string RegistryUtils::get_name(entt::entity entity) const{
    return registry_ptr->get<DescriptionComponent>(entity).name;
}

entt::entity RegistryUtils::get_room(entt::entity entity) {
    return room_by_entity[entity];
}

entt::entity RegistryUtils::get_random_by_tag(int tag, RandomNumberGenerator& rng) {
    const auto& elements_with_tag = get_by_tag(tag);
    if(elements_with_tag.empty()){
        return entt::null;
    }

    const unsigned int index = rng.random(elements_with_tag.size());

    return elements_with_tag[index];
}
