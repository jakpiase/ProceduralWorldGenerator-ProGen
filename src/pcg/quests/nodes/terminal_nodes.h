#pragma once

#include "src/game/item.h"
#include "src/pcg/quests/quest_expression.h"

namespace Quests::TerminalExpressions {

    class GoTo : public QuestExpression {
        entt::entity room;

    public:

        explicit GoTo(entt::entity room);

        std::unique_ptr<QuestNode> create_node(RegistryUtils& scene, RandomNumberGenerator& rng) override;
    };

    class Create : public QuestExpression {
        Item item;

    public:

        explicit Create(Item item);

        std::unique_ptr<QuestNode> create_node(RegistryUtils& scene, RandomNumberGenerator& rng) override;
    };

    class Discover : public QuestExpression {
    public:

        Discover() = default;

        std::unique_ptr<QuestNode> create_node(RegistryUtils& scene, RandomNumberGenerator& rng) override;
    };

    class Open : public QuestExpression {
        entt::entity room;

    public:

        explicit Open(entt::entity room);

        std::unique_ptr<QuestNode> create_node(RegistryUtils& scene, RandomNumberGenerator& rng) override;
    };

    class Kill : public QuestExpression {
        entt::entity enemy;

    public:

        explicit Kill(entt::entity enemy);

        std::unique_ptr<QuestNode> create_node(RegistryUtils& scene, RandomNumberGenerator& rng) override;
    };

    class Get : public QuestExpression {
        Item item;

    public:

        explicit Get(Item item);

        std::unique_ptr<QuestNode> create_node(RegistryUtils& scene, RandomNumberGenerator& rng) override;
    };

    class Poison : public QuestExpression {
        entt::entity target;

    public:

        explicit Poison(entt::entity target);

        std::unique_ptr<QuestNode> create_node(RegistryUtils& scene, RandomNumberGenerator& rng) override;
    };

    class Clear : public QuestExpression {
        entt::entity target;
        Item tool;

    public:

        explicit Clear(entt::entity target, Item tool);

        std::unique_ptr<QuestNode> create_node(RegistryUtils& scene, RandomNumberGenerator& rng) override;
    };

    class Find : public QuestExpression {
        Item item;

    public:

        explicit Find(Item item);

        std::unique_ptr<QuestNode> create_node(RegistryUtils& scene, RandomNumberGenerator& rng) override;
    };
}


