#include <format>
#include "src/pcg/quests/nodes/non_terminal_nodes.h"


Quests::NonTerminalExpressions::GoTo::GoTo(entt::entity room) : room(room) {}

std::unique_ptr<QuestNode> Quests::NonTerminalExpressions::GoTo::create_node(RegistryUtils& scene) {

    std::unique_ptr<MultiChildrenQuestNode> node = std::make_unique<MultiChildrenQuestNode>(
            std::format("Go to {}.", scene.get_name(room)));

    return evaluate_variants(scene, node);
}

Quests::NonTerminalExpressions::QuestExpressionVariants
Quests::NonTerminalExpressions::GoTo::generate_variants(RegistryUtils& scene) {
    QuestExpressionVariants variants(1);

    variants[0].emplace_back(std::make_unique<Quests::NonTerminalExpressions::GoTo>(room));

    return variants;
}

