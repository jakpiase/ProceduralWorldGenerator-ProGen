#include "src/random/linear_number_generator.h"

LinearNumberGenerator::LinearNumberGenerator(int base_seed)
                                            : RandomNumberGenerator(base_seed), modulus((1 << 16) + 1), multiplier(75), increment(74) {};

LinearNumberGenerator::LinearNumberGenerator(int base_seed, int modulus, int multiplier, int increment)
                                            : RandomNumberGenerator(base_seed), modulus(modulus), multiplier(multiplier), increment(increment) {};

int LinearNumberGenerator::next() const {
    return (multiplier * current_seed + increment) % modulus;
}
