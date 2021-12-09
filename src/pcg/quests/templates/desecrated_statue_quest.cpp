#include "src/pcg/room_content/room_content_type.h"
#include "src/pcg/quests/nodes/non_terminal_nodes.h"
#include "src/pcg/quests/templates/desecrated_statue_quest.h"

using namespace Quests;

std::unique_ptr<QuestNode>
Quests::Templates::DesecratedStatue::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {
    std::unique_ptr<MultiChildrenQuestNode> node = std::make_unique<MultiChildrenQuestNode>(
            "Consecrate the desecrated monument");

    return evaluate_variants(scene, rng, node);
}

NonTerminalExpressions::QuestExpressionVariants
Quests::Templates::DesecratedStatue::generate_variants(RegistryUtils& scene, RandomNumberGenerator& rng) {
    NonTerminalExpressions::QuestExpressionVariants variants(1);

    entt::entity monument_entity = scene.get_random_by_tag(RoomContentType::MONUMENT, rng);
    if (monument_entity == entt::null) {
        return NonTerminalExpressions::QuestExpressionVariants();
    }

    entt::entity monument_room = scene.get_room(monument_entity);
    Item holy_water("Sacred cleaners");

    variants[0].emplace_back(std::make_unique<Quests::NonTerminalExpressions::Get>(holy_water));
    variants[0].emplace_back(std::make_unique<Quests::NonTerminalExpressions::GoTo>(monument_room));
    variants[0].emplace_back(std::make_unique<Quests::TerminalExpressions::Clear>(monument_entity, holy_water));

    return variants;
}
