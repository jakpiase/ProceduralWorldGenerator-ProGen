#include "src/pcg/quests/nodes/multi_variant_quest_expression.h"


std::unique_ptr<QuestNode>
Quests::NonTerminalExpressions::MultiVariantQuestExpression::evaluate_variants(RegistryUtils& registry_utils,
                                                                               RandomNumberGenerator& rng,
                                                                               MultiChildrenQuestNodeUPtr& node) {
    for (auto& variant : generate_variants(registry_utils, rng)) {
        if (auto variant_node = evaluate_variant(registry_utils, rng, node, variant)) {
            return variant_node;
        } else {
            node->clear_children();
        }
    }

    return std::unique_ptr<QuestNode>();
}

std::unique_ptr<QuestNode>
Quests::NonTerminalExpressions::MultiVariantQuestExpression::evaluate_variant(RegistryUtils& registry,
                                                                              RandomNumberGenerator& rng,
                                                                              MultiChildrenQuestNodeUPtr& node,
                                                                              const QuestExpressionVariant& variant) {
    for (auto& expression : variant) {
        if (auto subquest_node = expression->create_node(registry, rng)) {
            node->add_child(subquest_node);
        } else {
            return std::unique_ptr<QuestNode>();
        }
    }

    return std::move(node);
}


