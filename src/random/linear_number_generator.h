#pragma once
#include "src/random/random_number_generator.h"

class LinearNumberGenerator : public RandomNumberGenerator {
public:
    // by default use ZX81's parameters
    LinearNumberGenerator(unsigned int base_seed = 12343);
    LinearNumberGenerator(unsigned int base_seed, unsigned int modulus, unsigned int multiplier, unsigned int increment);

protected:
    unsigned int next() const override;

private:
    const unsigned int modulus;
    const unsigned int multiplier;
    const unsigned int increment;
};
