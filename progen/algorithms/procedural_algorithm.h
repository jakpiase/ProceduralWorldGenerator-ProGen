#pragma once

#include <string>

class Game;

class ProceduralAlgorithm{
public:
    virtual std::string get_name() = 0;
    virtual void run(Game& game) = 0;
};
