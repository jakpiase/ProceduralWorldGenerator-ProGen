#include <memory>
#include <iostream>
#include <cstdlib>
#include "src/algorithms/algorithm.h"
#include "src/game/game.h"

class CaveCellularAutomata : public Algorithm{
private:
    int rock_percentage;
    int iterations;
    int neighbourhood_threshold;
    int neighbourhood_size;

public:
    CaveCellularAutomata(int rock_percentage, int iterations, int neighbourhood_threshold, int neighbourhood_size);
    int count_rock_neighboors(const std::vector<std::vector<tile>>& board, int x, int y);
    void run(Game& game) override;
};
