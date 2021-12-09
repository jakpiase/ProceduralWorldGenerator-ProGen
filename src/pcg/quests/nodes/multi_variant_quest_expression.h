#pragma once

#include <memory>
#include "src/pcg/quests/quest_node.h"
#include "src/pcg/utils/registry_utils.h"
#include "src/pcg/quests/quest_expression.h"

namespace Quests::NonTerminalExpressions {

    typedef std::unique_ptr<MultiChildrenQuestNode> MultiChildrenQuestNodeUPtr;
    typedef std::vector<QuestExpressionUPtr> QuestExpressionVariant;
    typedef std::vector<QuestExpressionVariant> QuestExpressionVariants;

    class MultiVariantQuestExpression : public QuestExpression {
    public:

        virtual QuestExpressionVariants generate_variants(RegistryUtils& registry_utils, RandomNumberGenerator& rng) = 0;

        std::unique_ptr<QuestNode> evaluate_variants(RegistryUtils& registry_utils,
                                                     RandomNumberGenerator& rng,
                                                     MultiChildrenQuestNodeUPtr& node);

    private:
        static std::unique_ptr<QuestNode>
        evaluate_variant(RegistryUtils& registry,
                         RandomNumberGenerator& rng,
                         MultiChildrenQuestNodeUPtr& node,
                         const QuestExpressionVariant& variant);
    };
}
