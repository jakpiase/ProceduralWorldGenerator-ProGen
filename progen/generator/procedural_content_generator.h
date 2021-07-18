#pragma once

#include <vector>
#include <memory>
#include "progen/algorithms/procedural_algorithm.h"

class ProceduralContentGenerator
{
private:
    std::vector<std::shared_ptr<ProceduralAlgorithm>> algorithms;
public:
    const std::vector<std::shared_ptr<ProceduralAlgorithm>>& get_algorithms();
    void push(std::shared_ptr<ProceduralAlgorithm>& algorithm);
    void generate(Game* game);
};
