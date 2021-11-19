#pragma once
#include "src/pcg/utils/random_iterators.h"

std::vector<int> fill_vector_with_range(int from, int to){
    int size = to - from + 1;
    std::vector<int> result;
    result.reserve(size);

    for (int i = from; i <= to; ++i) {
        result.push_back(i);
    }

    return result;
}

class RoomIterator {
    RandomIteratorPair<int, int> room_size_iterator;

public:
    RoomIterator(int min_size, int max_size, RandomNumberGenerator& rng)
            : room_size_iterator(RandomIterator<int>(fill_vector_with_range(min_size, max_size), rng),
                                 RandomIterator<int>(fill_vector_with_range(min_size, max_size), rng)) {}

    Dimensions2i next() {
        std::pair<int, int> room_size = room_size_iterator.next();
        return { room_size.first, room_size.second };
    }

    bool has_next() {
        return room_size_iterator.has_next();
    }
};

class CorridorIterator {
    RandomIteratorPair<int, Direction> corridor_iterator;

public:
    CorridorIterator(int min_size, int max_size, RandomNumberGenerator& rng)
            : corridor_iterator(RandomIterator<int>(fill_vector_with_range(min_size, max_size), rng),
                                RandomIterator<Direction>(std::vector(DIRECTIONS.begin(), DIRECTIONS.end()), rng)) {}

    std::pair<int, Direction> next() {
        return corridor_iterator.next();
    }

    bool has_next() {
        return corridor_iterator.has_next();
    }
};

