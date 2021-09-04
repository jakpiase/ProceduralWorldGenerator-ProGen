#pragma once

class RandomNumberGenerator{
public:
    RandomNumberGenerator(unsigned int base_seed = 1234);

    unsigned int random();
    unsigned int random(unsigned int max_value);
    bool random_bool();
    unsigned int get_seed() const;
    void set_seed(unsigned int seed);
    unsigned int get_base_seed() const;
    unsigned int get_number_of_generations() const;
protected:
    virtual unsigned int next() const = 0;
    unsigned int base_seed;
    unsigned int current_seed;
    unsigned int number_of_generations;
};
