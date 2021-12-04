#pragma once
#include <entt/entt.hpp>
#include <unordered_map>

class RegistryUtils {
private:
    std::unordered_map<int, std::vector<entt::entity>> entities_by_tag;
    std::unordered_map<entt::entity, std::vector<entt::entity>> entity_by_room;
    std::unordered_map<entt::entity, entt::entity> room_by_entity;
    

public:
    RegistryUtils() = default;


    const std::vector<entt::entity>& get_by_tag(int tag);

    void register_entity(entt::registry& registry, entt::entity entity, entt::entity room);

    void register_entity(entt::registry& registry, entt::entity entity);
};



