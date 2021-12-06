#include "src/pcg/room_content/room_content_type.h"
#include "src/pcg/quests/nodes/non_terminal_nodes.h"
#include "src/pcg/quests/templates/equipment_takeover_quest.h"

using namespace Quests;

std::unique_ptr<QuestNode>
Quests::Templates::EquipmentTakeover::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {
    std::unique_ptr<MultiChildrenQuestNode> node = std::make_unique<MultiChildrenQuestNode>("Equipment Takeover");

    return evaluate_variants(scene, rng, node);
}

NonTerminalExpressions::QuestExpressionVariants
Quests::Templates::EquipmentTakeover::generate_variants(RegistryUtils& scene, RandomNumberGenerator& rng) {
    NonTerminalExpressions::QuestExpressionVariants variants(1);

    entt::entity enemy_entity = scene.get_random_by_tag(RoomContentType::ENEMY, rng);
    if (enemy_entity == entt::null) {
        return NonTerminalExpressions::QuestExpressionVariants();
    }
    Item big_sword("The Big Sword");

    variants[0].emplace_back(std::make_unique<Quests::NonTerminalExpressions::Kill>(enemy_entity));
    variants[0].emplace_back(std::make_unique<Quests::TerminalExpressions::Get>(big_sword));

    return variants;
}
