#include <format>
#include "src/pcg/quests/nodes/non_terminal_nodes.h"

Quests::NonTerminalExpressions::Get::Get(Item item) : item(item) {}

std::unique_ptr<QuestNode> Quests::NonTerminalExpressions::Get::create_node(RegistryUtils& scene) {

    std::unique_ptr<MultiChildrenQuestNode> node = std::make_unique<MultiChildrenQuestNode>(
            std::format("Get holy water {}.", item.get_name()));

    return evaluate_variants(scene, node);
}

Quests::NonTerminalExpressions::QuestExpressionVariants
Quests::NonTerminalExpressions::Get::generate_variants(RegistryUtils& scene) {
    QuestExpressionVariants variants(1);

    //FIXME: get random place with waser
    variants[0].emplace_back(std::make_unique<Quests::NonTerminalExpressions::GoTo>(static_cast<entt::entity>(1)));
    variants[0].emplace_back(std::make_unique<Quests::TerminalExpressions::Get>(item));

    return variants;
}

