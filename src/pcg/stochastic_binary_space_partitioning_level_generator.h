#pragma once

#include <utility>
#include <sstream>
#include "src/core/scene.h"
#include "src/core/entity.h"
#include "src/pcg/simple_generators/simple_room_generator.h"
#include "src/pcg/corridor_generator.h"

class StochasticBinarySpacePartitioningLevelGenerator : public Generator {
    static constexpr float MAX_PROPORTION = 4.0f;
    static constexpr float MIN_PROPORTION = 1.0f/MAX_PROPORTION;
    const int minimal_split_size;
    const int minimal_room_size;
    const int bounding_box_padding;
    const bool maximum_spliting;
public:
    explicit StochasticBinarySpacePartitioningLevelGenerator(const BoundingBox& bounding_box, bool maximum_spliting = false)
            : minimal_split_size(80), bounding_box_padding(7), minimal_room_size(20), maximum_spliting(maximum_spliting), Generator(bounding_box){
                assert(minimal_split_size >= 2 * minimal_room_size + 4 * bounding_box_padding);
            }

    void run(Scene &scene) override;
private:
    bool can_be_splited(const BoundingBox& bounding_box);
    bool can_be_splited_vertically(const BoundingBox& bounding_box);
    bool can_be_splited_horizontally(const BoundingBox& bounding_box);
    bool get_split_orientation(const BoundingBox& bounding_box, RandomNumberGenerator* random_generator);
    BoundingBox generate_room(const BoundingBox& bounding_box, Scene& scene);
    std::pair<BoundingBox, BoundingBox> calculate_new_bounding_boxes(const BoundingBox& bounding_box, RandomNumberGenerator* random_generator);
    std::vector<BoundingBox> split_space(const BoundingBox& bounding_box, Scene& scene);
    std::pair<BoundingBox, BoundingBox> find_closest_rooms(const std::vector<BoundingBox>& first, const std::vector<BoundingBox>& second);
};



