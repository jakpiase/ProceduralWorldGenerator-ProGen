#pragma once

#include <vector>
#include <memory>
#include "src/algorithms/algorithm.h"

class Generator
{
private:
    std::vector<std::shared_ptr<Algorithm>> algorithms;
public:
    const std::vector<std::shared_ptr<Algorithm>>& get_algorithms();
    void push_back_algorithm(std::shared_ptr<Algorithm>& algorithm);
    void generate(Game& game);
};
