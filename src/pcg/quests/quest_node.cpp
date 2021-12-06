#include <utility>
#include <iostream>
#include "src/pcg/quests/quest_node.h"

QuestNode::QuestNode(std::string description) : description(std::move(description)) {}

void QuestNode::print_description(int depth) const {
    std::cout << std::string(depth, '-') << description << std::endl;
}

void MultiChildrenQuestNode::print_description(int depth) const {
    if (children.size() > 1) {
        QuestNode::print_description(depth);
        depth++;
    }
    for (auto& child : children) {
        child->print_description(depth);
    }
}
