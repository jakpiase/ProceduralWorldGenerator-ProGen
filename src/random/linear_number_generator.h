#pragma once
#include "src/random/random_number_generator.h"

class LinearNumberGenerator : public RandomNumberGenerator {
public:
    // by default use ZX81's parameters
    LinearNumberGenerator(int base_seed = 1234, int modulus = (1 << 16) + 1, int multiplier = 75, int increment = 74);

    int random() override;
private:
    const int modulus;
    const int multiplier;
    const int increment;
};
