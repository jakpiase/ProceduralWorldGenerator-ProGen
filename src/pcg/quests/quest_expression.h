#pragma once
#include <memory>
#include "src/pcg/quests/quest_node.h"
#include "src/core/scene.h"
#include "src/pcg/utils/registry_utils.h"


class QuestExpression {
public:
    virtual std::unique_ptr<QuestNode> create_node(RegistryUtils& registry_utils) = 0;
};

typedef std::unique_ptr<QuestExpression> QuestExpressionUPtr;



