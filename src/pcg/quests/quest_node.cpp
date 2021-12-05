#include <utility>
#include "src/pcg/quests/quest_node.h"

QuestNode::QuestNode(std::string  description) : description(std::move(description)) {}
