#include "src/pcg/agent_generators/agent_generator.h"

AgentGenerator::AgentGenerator(std::unique_ptr<Agent>&& agent, BoundingBox2i box, RandomNumberGenerator& rng)
        :   agent(std::move(agent)),
            rng(rng),
            Generator(box) {}

void AgentGenerator::run(Scene& scene) {
    Grid grid(bounding_box.get_width(), bounding_box.get_height());

    agent->run(scene, grid, rng);

}
