#include <iostream>
#include "src/game/game.h"
#include "src/algorithms/cave_cellular_automata.h"

int main() {
    Game game;
    game.print_board();
    std::shared_ptr<Algorithm> CCA = std::make_shared<CaveCellularAutomata>(50, 3, 5, 1);

    Generator generator = game.get_generator();
    generator.push_back_algorithm(CCA);
    generator.generate(game);
    game.print_board();

    return 0;
}
