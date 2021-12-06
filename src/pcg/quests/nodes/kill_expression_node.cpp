#include <format>
#include "src/pcg/quests/nodes/non_terminal_nodes.h"

Quests::NonTerminalExpressions::Kill::Kill(entt::entity enemy) : enemy(enemy) {}

std::unique_ptr<QuestNode>
Quests::NonTerminalExpressions::Kill::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {

    std::unique_ptr<MultiChildrenQuestNode> node = std::make_unique<MultiChildrenQuestNode>(
            std::format("Kill {}.", scene.get_name(enemy)));

    return evaluate_variants(scene, rng, node);
}

Quests::NonTerminalExpressions::QuestExpressionVariants
Quests::NonTerminalExpressions::Kill::generate_variants(RegistryUtils& scene, RandomNumberGenerator& rng) {
    QuestExpressionVariants variants(2);

    entt::entity room_with_enemy = scene.get_room(enemy);

    variants[0].emplace_back(std::make_unique<Quests::NonTerminalExpressions::Create>(Item("The essence of decay")));
    variants[0].emplace_back(std::make_unique<Quests::NonTerminalExpressions::GoTo>(room_with_enemy));
    variants[0].emplace_back(std::make_unique<Quests::TerminalExpressions::Poison>(enemy));

    variants[1].emplace_back(std::make_unique<Quests::NonTerminalExpressions::GoTo>(room_with_enemy));
    variants[1].emplace_back(std::make_unique<Quests::TerminalExpressions::Kill>(enemy));

    return variants;
}

