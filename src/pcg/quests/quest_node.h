#pragma once
#include <string>
#include <utility>
#include <vector>
#include <memory>


class QuestNode {
    std::string description;

public:
    explicit QuestNode(std::string description);

    virtual void print_description(int depth) const;
};

class MultiChildrenQuestNode : public QuestNode {
    std::vector<std::unique_ptr<QuestNode>> children;

public:
    explicit MultiChildrenQuestNode(std::string description) : QuestNode(std::move(description)) {}

    void print_description(int depth) const override;

    void add_child(std::unique_ptr<QuestNode>& child){
        children.push_back(std::move(child));
    }

    void clear_children(){
        children.clear();
    }
};




