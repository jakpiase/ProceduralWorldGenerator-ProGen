#include "linear_number_generator.h"

LinearNumberGenerator::LinearNumberGenerator(int base_seed, int modulus, int multiplier, int increment)
                                            : RandomNumberGenerator(base_seed), modulus(modulus), multiplier(multiplier), increment(increment) {};

int LinearNumberGenerator::random() {
    ++number_of_generations;
    current_seed = (multiplier * current_seed + increment) % modulus;
    return current_seed;
}
