#pragma once

#include <memory>
#include <vector>
#include "progen/generator/procedural_content_generator.h"
#include "progen/game/board_tile.h"

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20

class Game{
private:
    std::vector<std::vector<BoardTile>> board;
    ProceduralContentGenerator generator;
public:
    Game();
    void start();
    std::vector<std::vector<BoardTile>>& get_board();
    ProceduralContentGenerator& get_generator();
    void print_board();
};
