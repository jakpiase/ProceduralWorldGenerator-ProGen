#include <bits/stdc++.h>
#include "src/random/linear_number_generator.h"

LinearNumberGenerator::LinearNumberGenerator(unsigned int base_seed)
                                            : RandomNumberGenerator(base_seed), modulus(INT_MAX), multiplier(48271), increment(0) {};

LinearNumberGenerator::LinearNumberGenerator(unsigned int base_seed, unsigned int modulus, unsigned int multiplier, unsigned int increment)
                                            : RandomNumberGenerator(base_seed), modulus(modulus), multiplier(multiplier), increment(increment) {};

unsigned int LinearNumberGenerator::next() const {
    return (multiplier * current_seed + increment) % modulus;
}
