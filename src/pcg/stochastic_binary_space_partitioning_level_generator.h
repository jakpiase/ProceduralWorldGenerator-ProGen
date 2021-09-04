#pragma once

#include <utility>
#include <sstream>
#include "src/core/scene.h"
#include "src/core/entity.h"
#include "src/pcg/simple_generators/simple_room_generator.h"

class StochasticBinarySpacePartitioningLevelGenerator : public Generator {
    const int minimal_split_size;
    const int minimal_room_size;
    const int bounding_box_padding;
public:
    explicit StochasticBinarySpacePartitioningLevelGenerator(const BoundingBox& bounding_box)
            : minimal_split_size(70), minimal_room_size(minimal_split_size * 0.4), bounding_box_padding(5), Generator(bounding_box){}

    void run(Scene &scene) override;
private:
    bool can_be_splited(const BoundingBox& bounding_box);
    void generate_room(const BoundingBox& bounding_box, Scene& scene);
    std::pair<BoundingBox, BoundingBox> calculate_new_bounding_boxes(const BoundingBox& bounding_box, RandomNumberGenerator* random_generator);
    void split_space(const BoundingBox& bounding_box, Scene& scene);
};



