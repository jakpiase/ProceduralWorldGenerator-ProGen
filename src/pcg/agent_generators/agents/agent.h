#pragma once
#include "src/random/random_number_generator.h"
#include "src/pcg/grid.h"

class Agent {
public:
    virtual void run(Scene& scene, Grid& grid, RandomNumberGenerator& rng) = 0;
};
