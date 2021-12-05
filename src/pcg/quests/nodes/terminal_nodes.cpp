#include "src/pcg/quests/nodes/terminal_nodes.h"
#include "src/core/components/description_component.h"
#include <format>
#include <utility>

Quests::TerminalExpressions::GoTo::GoTo(entt::entity room) : room(room) {}

std::unique_ptr<QuestNode>
Quests::TerminalExpressions::GoTo::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {
    const std::string& room_name = scene.get_registry().get<DescriptionComponent>(room).name;
    const std::string description = std::format("Go to room named {}.", room_name);

    return std::make_unique<QuestNode>(description);
}

Quests::TerminalExpressions::Create::Create(Item item) : item(std::move(item)) {}

std::unique_ptr<QuestNode>
Quests::TerminalExpressions::Create::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {
    const std::string description = std::format("Create {}.", item.get_name());

    return std::make_unique<QuestNode>(description);
}

std::unique_ptr<QuestNode>
Quests::TerminalExpressions::Discover::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {
    const std::string description = "Discover the  mystery of the monument";

    return std::make_unique<QuestNode>(description);
}

Quests::TerminalExpressions::Open::Open(entt::entity room) : room(room) {}

std::unique_ptr<QuestNode>
Quests::TerminalExpressions::Open::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {
    const std::string& room_name = scene.get_registry().get<DescriptionComponent>(room).name;
    const std::string description = std::format("Open room named {}.", room_name);

    return std::make_unique<QuestNode>(description);
}

Quests::TerminalExpressions::Kill::Kill(entt::entity enemy) : enemy(enemy) {}

std::unique_ptr<QuestNode>
Quests::TerminalExpressions::Kill::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {
    const std::string& enemy_name = scene.get_name(enemy);
    const std::string description = std::format("Kill {}.", enemy_name);

    return std::make_unique<QuestNode>(description);
}

Quests::TerminalExpressions::Get::Get(Item item) : item(std::move(item)) {}

std::unique_ptr<QuestNode>
Quests::TerminalExpressions::Get::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {
    const std::string description = std::format("Pickup {}.", item.get_name());

    return std::make_unique<QuestNode>(description);
}

Quests::TerminalExpressions::Poison::Poison(entt::entity target) : target(target) {}

std::unique_ptr<QuestNode>
Quests::TerminalExpressions::Poison::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {
    const std::string& target_name = scene.get_name(target);
    const std::string description = std::format("Poison {}.", target_name);

    return std::make_unique<QuestNode>(description);
}

Quests::TerminalExpressions::Clear::Clear(entt::entity target, Item tool) : target(target), tool(std::move(tool)) {}

std::unique_ptr<QuestNode>
Quests::TerminalExpressions::Clear::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {
    const std::string& target_name = scene.get_name(target);
    const std::string description = std::format("Clear {}.", target_name);

    return std::make_unique<QuestNode>(description);
}

Quests::TerminalExpressions::Find::Find(Item item) : item(std::move(item)){}

std::unique_ptr<QuestNode>
Quests::TerminalExpressions::Find::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {
    const std::string description = std::format("Find {}.", item.get_name());


    //TODO: add postCreateMethod
    return std::make_unique<QuestNode>(description);
}
