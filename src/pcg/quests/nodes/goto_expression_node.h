#pragma once
#include <vector>
#include <memory>
#include "src/game/item.h"
#include "src/pcg/quests/quest_expression.h"
#include "src/pcg/quests/nodes/multi_variant_quest_expression.h"

namespace Quests::NonTerminalExpressions {

    class GoTo : public MultiVariantQuestExpression{
        entt::entity room;

    public:
        explicit GoTo(entt::entity room);

        std::unique_ptr<QuestNode> create_node(RegistryUtils& scene, RandomNumberGenerator& rng) override;

        QuestExpressionVariants generate_variants(RegistryUtils& scene, RandomNumberGenerator& rng) override;
    };

}


