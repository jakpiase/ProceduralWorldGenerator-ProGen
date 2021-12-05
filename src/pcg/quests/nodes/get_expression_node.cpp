#include <format>
#include <utility>
#include "src/pcg/room_content/room_content_type.h"
#include "src/pcg/quests/nodes/non_terminal_nodes.h"

Quests::NonTerminalExpressions::Get::Get(Item item) : item(std::move(item)) {}

std::unique_ptr<QuestNode>
Quests::NonTerminalExpressions::Get::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {

    std::unique_ptr<MultiChildrenQuestNode> node = std::make_unique<MultiChildrenQuestNode>(
            std::format("Get holy water {}.", item.get_name()));

    return evaluate_variants(scene, rng, node);
}

Quests::NonTerminalExpressions::QuestExpressionVariants
Quests::NonTerminalExpressions::Get::generate_variants(RegistryUtils& scene, RandomNumberGenerator& rng) {
    QuestExpressionVariants variants(1);

    entt::entity water_entity = scene.get_random_by_tag(RoomContentType::WATER, rng);
    entt::entity room_with_water = scene.get_room(water_entity);

    variants[0].emplace_back(std::make_unique<Quests::NonTerminalExpressions::GoTo>(room_with_water));
    variants[0].emplace_back(std::make_unique<Quests::TerminalExpressions::Get>(item));

    return variants;
}

