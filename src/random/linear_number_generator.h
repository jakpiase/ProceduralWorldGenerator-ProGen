#pragma once
#include "src/random/random_number_generator.h"

class LinearNumberGenerator : public RandomNumberGenerator {
public:
    // by default use ZX81's parameters
    LinearNumberGenerator(int base_seed = 1234);
    LinearNumberGenerator(int base_seed, int modulus, int multiplier, int increment);

    int next() override;
private:
    const int modulus;
    const int multiplier;
    const int increment;
};
