#pragma once

#include <memory>
#include "src/pcg/quests/quest_expression.h"
#include "src/pcg/quests/nodes/multi_variant_quest_expression.h"

namespace Quests::Templates {

    class HolyBath : public Quests::NonTerminalExpressions::MultiVariantQuestExpression {
    public:
        std::unique_ptr<QuestNode> create_node(RegistryUtils& scene, RandomNumberGenerator& rng) override;

        Quests::NonTerminalExpressions::QuestExpressionVariants
        generate_variants(RegistryUtils& scene, RandomNumberGenerator& rng) override;
    };

}


