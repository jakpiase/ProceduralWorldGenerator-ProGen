#include "progen/generator/procedural_content_generator.h"
#include <iostream>

const std::vector<std::shared_ptr<ProceduralAlgorithm>>& ProceduralContentGenerator::get_algorithms(){
    return algorithms;
}

void ProceduralContentGenerator::push(std::shared_ptr<ProceduralAlgorithm>& algorithm){
    algorithms.push_back(algorithm);
}

void ProceduralContentGenerator::generate(Game* game){
    for(size_t i=0 ; i<algorithms.size(); ++i){
        std::cout << "Running algorithm " << algorithms[i]->get_name() << std::endl;
        algorithms[i]->run(*game);
    }
}
