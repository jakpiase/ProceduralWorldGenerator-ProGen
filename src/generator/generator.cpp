#include "src/generator/generator.h"
#include <iostream>

const std::vector<std::shared_ptr<Algorithm>>& Generator::get_algorithms(){
    return algorithms;
}

void Generator::push_back_algorithm(std::shared_ptr<Algorithm>& algorithm){
    algorithms.push_back(algorithm);
}

void Generator::generate(Game& game){
    for(size_t i=0 ; i<algorithms.size(); ++i){
        algorithms[i]->run(game);
    }
}