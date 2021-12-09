#include "src/pcg/room_content/room_content_type.h"
#include "src/pcg/quests/nodes/non_terminal_nodes.h"

Quests::NonTerminalExpressions::Open::Open(entt::entity room) : room(room) {}

std::unique_ptr<QuestNode>
Quests::NonTerminalExpressions::Open::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {

    std::unique_ptr<MultiChildrenQuestNode> node = std::make_unique<MultiChildrenQuestNode>(
            "Open " + scene.get_name(room) + ".");

    return evaluate_variants(scene, rng, node);
}

Quests::NonTerminalExpressions::QuestExpressionVariants
Quests::NonTerminalExpressions::Open::generate_variants(RegistryUtils& scene, RandomNumberGenerator& rng) {
    QuestExpressionVariants variants(2);

    const Item room_key = Item("Key to " + scene.get_name(room));

    entt::entity enemy = scene.get_random_by_tag(RoomContentType::ENEMY, rng);
    variants[0].emplace_back(std::make_unique<Quests::NonTerminalExpressions::Kill>(enemy));
    variants[0].emplace_back(std::make_unique<Quests::TerminalExpressions::Get>(room_key));
    variants[0].emplace_back(std::make_unique<Quests::TerminalExpressions::Open>(room));

    variants[1].emplace_back(std::make_unique<Quests::TerminalExpressions::Find>(room_key));
    variants[1].emplace_back(std::make_unique<Quests::TerminalExpressions::Open>(room));

    return variants;
}

