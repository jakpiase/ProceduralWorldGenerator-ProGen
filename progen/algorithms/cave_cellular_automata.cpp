#include <vector>
#include "progen/algorithms/cave_cellular_automata.h"

CaveCellularAutomata::CaveCellularAutomata(int rock_percentage, int iterations, int neighbourhood_threshold, int neighbourhood_size) {
    this->rock_percentage = rock_percentage;
    this->iterations = iterations;
    this->neighbourhood_threshold = neighbourhood_threshold;
    this->neighbourhood_size = neighbourhood_size;
}

int CaveCellularAutomata::count_rock_neighboors(const std::vector<std::vector<BoardTile>>& board, int x, int y){
    int rock_neighboors = 0;

    for(size_t i = x - neighbourhood_size; i <= x + neighbourhood_size; ++i){
        for(size_t j = y - neighbourhood_size; j <= y + neighbourhood_size; ++j){
            if (board[i][j] == BoardTile::rock)
                ++rock_neighboors;
        } 
    }

    return rock_neighboors;
}

std::string CaveCellularAutomata::get_name() {
    return "CaveCellularAutomata";
}

void CaveCellularAutomata::initialize_board(std::vector<std::vector<BoardTile>>& board) {
    for(size_t i=0; i<board.size(); ++i){
        for(size_t j=0;j<board[i].size(); ++j){
                if(rand()%100 < rock_percentage)
                    board[i][j] = BoardTile::rock;
        }
    }
}

void CaveCellularAutomata::run(Game& game) {
    //std::cout<< "Running " << get_name() << " algorithm" << std::endl; 
    auto board_copy(game.get_board());
    initialize_board(board_copy);
    

    for(int i=0; i<iterations; ++i){
        for(int j=neighbourhood_size; j<board_copy.size() - neighbourhood_size; ++j){
            for(int k=neighbourhood_size; k<board_copy.size() - neighbourhood_size; ++k){
                game.get_board()[j][k] = count_rock_neighboors(board_copy, j, k) >= neighbourhood_threshold ? BoardTile::rock : BoardTile::empty;
            }
        }
        board_copy = game.get_board();
    }
}
