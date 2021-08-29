#include <bits/stdc++.h>
#include "src/random/linear_number_generator.h"

LinearNumberGenerator::LinearNumberGenerator(int base_seed)
                                            : RandomNumberGenerator(base_seed), modulus(INT_MAX), multiplier(48271), increment(0) {};

LinearNumberGenerator::LinearNumberGenerator(int base_seed, int modulus, int multiplier, int increment)
                                            : RandomNumberGenerator(base_seed), modulus(modulus), multiplier(multiplier), increment(increment) {};

int LinearNumberGenerator::next() const {
    return (unsigned int)(multiplier * current_seed + increment) % modulus;
}
