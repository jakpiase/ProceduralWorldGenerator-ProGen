#include "random_number_generator.h"

RandomNumberGenerator::RandomNumberGenerator(unsigned int seed): base_seed(seed), current_seed(seed), number_of_generations(0) {};

unsigned int RandomNumberGenerator::random() {
    ++number_of_generations;
    return current_seed = next();
}

unsigned int RandomNumberGenerator::random(unsigned int max_value) {
    return random() % max_value;
}

bool RandomNumberGenerator::random_bool() {
    return (random() & 0x100);
}

unsigned int RandomNumberGenerator::get_seed() const {
    return current_seed;
}

void RandomNumberGenerator::set_seed(unsigned int seed) {
    base_seed = current_seed = seed;
    number_of_generations = 0;
}

unsigned int RandomNumberGenerator::get_base_seed() const {
    return base_seed;
}

unsigned int RandomNumberGenerator::get_number_of_generations() const {
    return number_of_generations;
}
