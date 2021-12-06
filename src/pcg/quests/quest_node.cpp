#include <utility>
#include <iostream>
#include "src/pcg/quests/quest_node.h"

QuestNode::QuestNode(std::string description) : description(std::move(description)) {}

QuestNode::QuestNode(std::string description, std::function<void()> post_construct) : QuestNode(
        std::move(description)) {
    post_construct_method = std::move(post_construct);
}

void QuestNode::print_description(int depth) const {
    std::cout << std::string(depth, '-') << description << std::endl;
}

void QuestNode::post_construct() {
    if (post_construct_method) {
        post_construct_method();
    }
}

void QuestNode::set_post_construct(std::function<void()> method) {
    post_construct_method = std::move(method);
}

MultiChildrenQuestNode::MultiChildrenQuestNode(std::string description) : QuestNode(std::move(description)) {
    set_post_construct([this] { post_construct_method(); });
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

void MultiChildrenQuestNode::post_construct_method() {
    for (auto& child : children) {
        child->post_construct();
    }
}

