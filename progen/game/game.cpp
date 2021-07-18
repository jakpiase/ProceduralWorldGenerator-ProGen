#include <iostream>
#include "progen/game/game.h"

Game::Game(){
    board = std::vector<std::vector<BoardTile>>(BOARD_HEIGHT, std::vector<BoardTile>(BOARD_HEIGHT, BoardTile::empty));
}

void Game::start(){
    // TODO jakpiase / wrobcio789
    // argument will be changed to "model" after consulting program architecture
    generator.generate(this);
}

std::vector<std::vector<BoardTile>>& Game::get_board(){
    return board;
}

ProceduralContentGenerator& Game::get_generator(){
    return generator;
}

void Game::print_board(){
    for(size_t i=0 ; i<board.size() ; ++i){
        for(size_t j=0; j<board[i].size(); ++j){
            std::cout<<static_cast<int>(board[i][j]) << " ";
        }
        std::cout<<std::endl;
    }
}
