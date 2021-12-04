#include <entt/entity/registry.hpp>
#include "src/pcg/utils/registry_utils.h"
#include "src/core/components/description_component.h"


const std::vector<entt::entity>& RegistryUtils::get_by_tag(int tag) {
    return entities_by_tag[tag];
}

void RegistryUtils::register_entity(entt::registry& registry, entt::entity entity, entt::entity room) {
    room_by_entity[entity] = room;
    entity_by_room[room].push_back(entity);

    register_entity(registry, entity);
}

void RegistryUtils::register_entity(entt::registry& registry, entt::entity entity) {
    DescriptionComponent& description_component = registry.get<DescriptionComponent>(entity);
    entities_by_tag[description_component.tag].push_back(entity);
}
