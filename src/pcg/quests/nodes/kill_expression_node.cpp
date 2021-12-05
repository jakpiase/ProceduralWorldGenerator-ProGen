#include <format>
#include "src/pcg/quests/nodes/non_terminal_nodes.h"

Quests::NonTerminalExpressions::Kill::Kill(entt::entity enemy) : enemy(enemy) {}

std::unique_ptr<QuestNode> Quests::NonTerminalExpressions::Kill::create_node(RegistryUtils& scene) {

    std::unique_ptr<MultiChildrenQuestNode> node = std::make_unique<MultiChildrenQuestNode>(
            std::format("Kill {}.", scene.get_name(enemy)));

    return evaluate_variants(scene, node);
}

Quests::NonTerminalExpressions::QuestExpressionVariants
Quests::NonTerminalExpressions::Kill::generate_variants(RegistryUtils& scene) {
    QuestExpressionVariants variants(1);

    variants[0].emplace_back(std::make_unique<Quests::NonTerminalExpressions::Create>(Item("The essence of decay")));

    return variants;
}

