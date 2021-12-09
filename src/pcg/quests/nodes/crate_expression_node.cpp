#include <utility>
#include <format>
#include "src/pcg/quests/nodes/non_terminal_nodes.h"

Quests::NonTerminalExpressions::Create::Create(Item item) : item(std::move(item)) {}

std::unique_ptr<QuestNode>
Quests::NonTerminalExpressions::Create::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {

    std::unique_ptr<MultiChildrenQuestNode> node = std::make_unique<MultiChildrenQuestNode>(
            "Create " + item.get_name() + ".");

    return evaluate_variants(scene, rng, node);
}

Quests::NonTerminalExpressions::QuestExpressionVariants
Quests::NonTerminalExpressions::Create::generate_variants(RegistryUtils& scene, RandomNumberGenerator& rng) {
    QuestExpressionVariants variants(3);

    variants[0].emplace_back(std::make_unique<Quests::TerminalExpressions::Find>(Item("red flower")));
    variants[0].emplace_back(std::make_unique<Quests::TerminalExpressions::Find>(Item("stinky honey")));
    variants[0].emplace_back(std::make_unique<Quests::TerminalExpressions::Find>(Item("gold coal")));
    variants[0].emplace_back(std::make_unique<Quests::TerminalExpressions::Create>(item));

    variants[1].emplace_back(std::make_unique<Quests::TerminalExpressions::Find>(Item("dwarvish grease")));
    variants[1].emplace_back(std::make_unique<Quests::TerminalExpressions::Find>(Item("lightning crystal")));
    variants[1].emplace_back(std::make_unique<Quests::TerminalExpressions::Create>(item));

    variants[2].emplace_back(std::make_unique<Quests::TerminalExpressions::Find>(Item("High quality oil")));
    variants[2].emplace_back(std::make_unique<Quests::TerminalExpressions::Create>(item));

    return variants;
}


