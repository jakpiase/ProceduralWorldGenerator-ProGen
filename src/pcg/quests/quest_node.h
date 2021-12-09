#pragma once
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <functional>


class QuestNode {
    std::string description;
    std::function<void()> post_construct_method;

public:
    explicit QuestNode(std::string description);
    QuestNode(std::string description, std::function<void()> post_construct);

    virtual void print_description(int depth) const;

    void post_construct();

    void set_post_construct(std::function<void()> method);
};

class MultiChildrenQuestNode : public QuestNode {
    std::vector<std::unique_ptr<QuestNode>> children;

public:
    explicit MultiChildrenQuestNode(std::string description);

    void print_description(int depth) const override;

    void add_child(std::unique_ptr<QuestNode>& child){
        children.push_back(std::move(child));
    }

    void clear_children(){
        children.clear();
    }

private:
    void post_construct_method();
};




