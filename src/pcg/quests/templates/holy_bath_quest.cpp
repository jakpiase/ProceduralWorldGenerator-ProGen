#include "src/pcg/room_content/room_content_type.h"
#include "src/pcg/quests/nodes/non_terminal_nodes.h"
#include "src/pcg/quests/templates/holy_bath_quest.h"

using namespace Quests;

std::unique_ptr<QuestNode>
Quests::Templates::HolyBath::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {
    std::unique_ptr<MultiChildrenQuestNode> node = std::make_unique<MultiChildrenQuestNode>("Bathe in ");

    return evaluate_variants(scene, rng, node);
}

NonTerminalExpressions::QuestExpressionVariants
Quests::Templates::HolyBath::generate_variants(RegistryUtils& scene, RandomNumberGenerator& rng) {
    NonTerminalExpressions::QuestExpressionVariants variants(1);

    entt::entity water_entity = scene.get_random_by_tag(RoomContentType::WATER, rng);
    entt::entity water_room = scene.get_room(water_entity);
    Item holy_grease("Holy grease");

    variants[0].emplace_back(std::make_unique<Quests::NonTerminalExpressions::Create>(holy_grease));
    variants[0].emplace_back(std::make_unique<Quests::NonTerminalExpressions::GoTo>(water_room));
    variants[0].emplace_back(std::make_unique<Quests::TerminalExpressions::Bathe>(holy_grease, water_entity));

    return variants;
}
