#include "src/algorithms/algorithm.h"
#include <iostream>

Algorithm::Algorithm(std::string name) : name(name){}

std::string Algorithm::get_name(){
    return name;
}
