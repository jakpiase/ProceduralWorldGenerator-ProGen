#pragma once

class RandomNumberGenerator{
public:
    RandomNumberGenerator(int base_seed = 1234);

    virtual int random() = 0;
    int get_seed() const;
    void set_seed(int seed);
    int get_base_seed() const;
    int get_number_of_generations() const;
protected:
    int base_seed;
    int current_seed;
    int number_of_generations;
};
