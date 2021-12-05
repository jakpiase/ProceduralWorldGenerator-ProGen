#include <format>
#include "src/pcg/quests/nodes/non_terminal_nodes.h"

Quests::NonTerminalExpressions::Open::Open(entt::entity room) : room(room) {}

std::unique_ptr<QuestNode> Quests::NonTerminalExpressions::Open::create_node(RegistryUtils& scene) {

    std::unique_ptr<MultiChildrenQuestNode> node = std::make_unique<MultiChildrenQuestNode>(
            std::format("Open {}.", scene.get_name(room)));

    return evaluate_variants(scene, node);
}

Quests::NonTerminalExpressions::QuestExpressionVariants
Quests::NonTerminalExpressions::Open::generate_variants(RegistryUtils& scene) {
    QuestExpressionVariants variants(2);

    const Item room_key = Item(std::format("Key to {}", scene.get_name(room)));

    //FIXME: Random enemy to kill
    variants[0].emplace_back(std::make_unique<Quests::NonTerminalExpressions::Kill>(room));
    variants[0].emplace_back(
            std::make_unique<Quests::TerminalExpressions::Get>(room_key));
    variants[0].emplace_back(std::make_unique<Quests::TerminalExpressions::Open>(room));

    variants[1].emplace_back(std::make_unique<Quests::TerminalExpressions::Find>(room_key));
    variants[1].emplace_back(std::make_unique<Quests::TerminalExpressions::Open>(room));

    return variants;
}

