#pragma once

class RandomNumberGenerator{
public:
    explicit RandomNumberGenerator(unsigned int base_seed = 1234);

    unsigned int random();
    unsigned int random(unsigned int max_value);
    unsigned int random(unsigned int min_value, unsigned int max_value);
    bool random_bool();
    [[nodiscard]] unsigned int get_seed() const;
    void set_seed(unsigned int seed);
    [[nodiscard]] unsigned int get_base_seed() const;
    [[nodiscard]] unsigned int get_number_of_generations() const;
protected:
    virtual unsigned int next() const = 0;
    unsigned int base_seed;
    unsigned int current_seed;
    unsigned int number_of_generations;
};
