#include "src/pcg/quests/nodes/non_terminal_nodes.h"


Quests::NonTerminalExpressions::GoTo::GoTo(entt::entity room) : room(room) {}

std::unique_ptr<QuestNode>
Quests::NonTerminalExpressions::GoTo::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {

    std::unique_ptr<MultiChildrenQuestNode> node = std::make_unique<MultiChildrenQuestNode>(
            "Enter " + scene.get_name(room) + ".");

    return evaluate_variants(scene, rng, node);
}

Quests::NonTerminalExpressions::QuestExpressionVariants
Quests::NonTerminalExpressions::GoTo::generate_variants(RegistryUtils& scene, RandomNumberGenerator& rng) {
    QuestExpressionVariants variants(2);

    variants[0].emplace_back(std::make_unique<Quests::TerminalExpressions::GoTo>(room));

    variants[1].emplace_back(std::make_unique<Quests::NonTerminalExpressions::Open>(room));
    variants[1].emplace_back(std::make_unique<Quests::TerminalExpressions::GoTo>(room));

    return variants;
}

