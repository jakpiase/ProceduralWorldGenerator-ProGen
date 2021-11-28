#pragma once
#include <vector>

template<typename T>
class RandomIterator {
    RandomNumberGenerator& rng;
    std::vector<T> elements;
    size_t index = 0;

public:
    explicit RandomIterator(std::vector<T>&& elements, RandomNumberGenerator& rng)
            : rng(rng),
              elements(std::move(elements)) {
        shuffle();
    }

    T next(bool should_increment = true) {
        assert((has_next()));

        return elements[should_increment ? index++ : index];
    }

    bool has_next() {
        return index < elements.size();
    }

    void reset() {
        index = 0;
        shuffle();
    }


private:
    void shuffle() { auto random_number_engine =
        std::mersenne_twister_engine<unsigned int, 32, 624, 397, 31, 0x9908b0df, 11, 0xffffffff, 7,
                                     0x9d2c5680, 15,0xefc60000, 18, 1812433253>(rng.random());
        std::shuffle(elements.begin(), elements.end(), random_number_engine);
    }

};

template<typename T, typename K>
class RandomIteratorPair {
    RandomIterator<T> first;
    RandomIterator<K> second;


public:
    RandomIteratorPair(RandomIterator<T>&& first, RandomIterator<K>&& second)
            : first(std::move(first)), second(std::move(second)) {}

    std::pair<T, K> next() {
        const T first_result = first.next();
        const bool should_reset_first = !first.has_next();
        const K second_result = second.next(should_reset_first);

        if (should_reset_first) {
            first.reset();
        }

        return std::make_pair(first_result, second_result);
    }

    bool has_next() {
        return second.has_next();
    }
};
