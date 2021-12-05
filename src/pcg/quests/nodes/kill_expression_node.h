#pragma once
#include <vector>
#include <memory>
#include "src/game/item.h"
#include "src/pcg/quests/quest_expression.h"
#include "src/pcg/quests/nodes/multi_variant_quest_expression.h"

namespace Quests::NonTerminalExpressions {

    class Kill : public MultiVariantQuestExpression{
        entt::entity enemy;

    public:
        explicit Kill(entt::entity enemy);

        std::unique_ptr<QuestNode> create_node(RegistryUtils& scene) override;

        QuestExpressionVariants generate_variants(RegistryUtils& scene) override;
    };

}


