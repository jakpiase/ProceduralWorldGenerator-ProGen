#include <vector>
#include "src/algorithms/cave_cellular_automata.h"

CaveCellularAutomata::CaveCellularAutomata(int rock_percentage, int iterations, int neighbourhood_threshold, int neighbourhood_size) : Algorithm(std::string("CaveCellularAutomata")) {
    this->rock_percentage = rock_percentage;
    this->iterations = iterations;
    this->neighbourhood_threshold = neighbourhood_threshold;
    this->neighbourhood_size = neighbourhood_size;
}

int CaveCellularAutomata::count_rock_neighboors(const std::vector<std::vector<tile>>& board, int x, int y){
    int rock_neighboors = 0;

    for(size_t i = x - neighbourhood_size; i <= x + neighbourhood_size; ++i){
        for(size_t j = y - neighbourhood_size; j <= y + neighbourhood_size; ++j){
            if (board[i][j] == tile::rock)
                ++rock_neighboors;
        } 
    }

    return rock_neighboors;
}

void CaveCellularAutomata::run(Game& game) {
  std::cout<< "Running " << get_name() << " algorithm" << std::endl; 
  auto board_copy(game.get_board());

  for(size_t i=0; i<board_copy.size(); ++i){
      for(size_t j=0;j<board_copy[i].size(); ++j){
            if(rand()%100 < rock_percentage)
                board_copy[i][j] = tile::rock;
      }
  }

    for(int i=0; i<iterations ; ++i){
        for(int j=neighbourhood_size; j<board_copy.size() - neighbourhood_size; ++j){
            for(int k=neighbourhood_size; k<board_copy.size() - neighbourhood_size; ++k){
                game.get_board()[j][k] = count_rock_neighboors(board_copy, j, k) >= neighbourhood_threshold ? tile::rock : tile::empty;
            }
        }
        board_copy = game.get_board();
    }
}
