#include "random_number_generator.h"

RandomNumberGenerator::RandomNumberGenerator(int seed): base_seed(seed), current_seed(seed), number_of_generations(0) {};

int RandomNumberGenerator::get_seed() const {
    return current_seed;
}

void RandomNumberGenerator::set_seed(int seed) {
    base_seed = current_seed = seed;
    number_of_generations = 0;
}

int RandomNumberGenerator::get_base_seed() const {
    return base_seed;
}

int RandomNumberGenerator::get_number_of_generations() const {
    return number_of_generations;
}
