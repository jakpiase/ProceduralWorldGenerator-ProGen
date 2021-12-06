#include <random>
#include "src/pcg/quests/nodes/multi_variant_quest_expression.h"


std::unique_ptr<QuestNode>
Quests::NonTerminalExpressions::MultiVariantQuestExpression::evaluate_variants(RegistryUtils& registry_utils,
                                                                               RandomNumberGenerator& rng,
                                                                               MultiChildrenQuestNodeUPtr& node) {
    QuestExpressionVariants variants = generate_variants(registry_utils, rng);

    auto random_number_engine =
            std::mersenne_twister_engine<unsigned int, 32, 624, 397, 31, 0x9908b0df, 11, 0xffffffff, 7,
                    0x9d2c5680, 15,0xefc60000, 18, 1812433253>(rng.random());
    std::shuffle(variants.begin(), variants.end(), random_number_engine);

    for (auto& variant : variants) {
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


