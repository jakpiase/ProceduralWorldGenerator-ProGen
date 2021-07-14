#pragma once

#include <string>

class Game;

class Algorithm{
private:
    std::string name;
public:
    Algorithm(std::string name);
    std::string get_name();
    virtual void run(Game& game) = 0;
};
