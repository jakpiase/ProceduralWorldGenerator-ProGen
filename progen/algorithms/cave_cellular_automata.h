#include <memory>
#include <iostream>
#include <cstdlib>
#include "progen/algorithms/procedural_algorithm.h"
#include "progen/game/game.h"

class CaveCellularAutomata : public ProceduralAlgorithm{
private:
    int rock_percentage;
    int iterations;
    int neighbourhood_threshold;
    int neighbourhood_size;

    int count_rock_neighboors(const std::vector<std::vector<BoardTile>>& board, int x, int y);
    void initialize_board(std::vector<std::vector<BoardTile>>& board);
public:
    CaveCellularAutomata(int rock_percentage, int iterations, int neighbourhood_threshold, int neighbourhood_size);
    std::string get_name() override;
    void run(Game& game) override;
};
