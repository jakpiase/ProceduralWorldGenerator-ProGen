#include <iostream>
#include "progen/game/game.h"
#include "progen/algorithms/cave_cellular_automata.h"

int main() {
    Game game;
    std::shared_ptr<ProceduralAlgorithm> CCA = std::make_shared<CaveCellularAutomata>(50, 3, 5, 1);
    ProceduralContentGenerator& generator = game.get_generator();
    generator.push(CCA);
    
    game.print_board();
    game.start();
    game.print_board();

    return 0;
}
