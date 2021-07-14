#pragma once

#include <memory>
#include <vector>
#include "src/generator/generator.h"
#include "src/game/tile.h"

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20

class Game{
private:
    std::vector<std::vector<tile>> board;
    Generator generator;
public:
    Game();
    std::vector<std::vector<tile>>& get_board();
    Generator& get_generator();
    void print_board();
};
