#include <iostream>
#include "src/game/game.h"

Game::Game(){
    board = std::vector<std::vector<tile>>(BOARD_HEIGHT, std::vector<tile>(BOARD_HEIGHT, tile::empty));
}

std::vector<std::vector<tile>>& Game::get_board(){
    return board;
}

Generator& Game::get_generator(){
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
