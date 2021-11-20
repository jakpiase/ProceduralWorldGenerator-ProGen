#pragma once

#include "src/pcg/generator.h"
#include "src/pcg/agent_generators/agents/agent.h"
#include "src/random/random_number_generator.h"

class AgentGenerator : public Generator {
    std::unique_ptr<Agent> agent;
    RandomNumberGenerator& rng;

public:
    AgentGenerator(std::unique_ptr<Agent>&& agent, BoundingBox2i box, RandomNumberGenerator& rng);

    void run(Scene& scene) override;
};



