#include "src/pcg/room_content/room_content_type.h"
#include "src/pcg/quests/nodes/non_terminal_nodes.h"
#include "src/pcg/quests/templates/monument_mystery_quest.h"

using namespace Quests;

std::unique_ptr<QuestNode>
Quests::Templates::MonumentMystery::create_node(RegistryUtils& scene, RandomNumberGenerator& rng) {
    std::unique_ptr<MultiChildrenQuestNode> node = std::make_unique<MultiChildrenQuestNode>("Discover the mystery of the monument");

    return evaluate_variants(scene, rng, node);
}

NonTerminalExpressions::QuestExpressionVariants
Quests::Templates::MonumentMystery::generate_variants(RegistryUtils& scene, RandomNumberGenerator& rng) {
    NonTerminalExpressions::QuestExpressionVariants variants(1);

    entt::entity monument_entity = scene.get_random_by_tag(RoomContentType::MONUMENT, rng);
    entt::entity monument_room = scene.get_room(monument_entity);
    Item formless_shining_matter("Formless Shining Matter");

    variants[0].emplace_back(std::make_unique<Quests::NonTerminalExpressions::Create>(formless_shining_matter));
    variants[0].emplace_back(std::make_unique<Quests::NonTerminalExpressions::GoTo>(monument_room));
    variants[0].emplace_back(std::make_unique<Quests::TerminalExpressions::Discover>(monument_entity));

    return variants;
}
