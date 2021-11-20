#pragma once

#include <utility>
#include <sstream>
#include "src/core/scene.h"
#include "src/core/entity.h"
#include "src/pcg/simple_generators/simple_room_generator.h"
#include "src/pcg/corridor_generator.h"
#include "src/pcg/grid.h"

class StochasticBinarySpacePartitioningLevelGenerator : public Generator {
    static constexpr float MAX_PROPORTION = 3.5f;
    static constexpr float MIN_PROPORTION = 1.0f/MAX_PROPORTION;
    const int minimal_split_size;
    const int minimal_room_size;
    const int maximal_room_size;
    const int bounding_box_padding;

    const bool maximum_spliting;
    std::shared_ptr<Grid> grid;
    RandomNumberGenerator& rng;
public:
    // minimal_split_size - the higher the value, the less room will be generated
    // bounding_box_padding - room padding from split bounding box
    // minimal_room_size - smallest possible value for width and height of generated room
    // maximal_room_size - highest possible value for width and height of generated room
    explicit StochasticBinarySpacePartitioningLevelGenerator(const BoundingBox2i& bounding_box, RandomNumberGenerator& rng, bool maximum_spliting = true)
            : minimal_split_size(25), bounding_box_padding(1), minimal_room_size(6), maximal_room_size(16),
              maximum_spliting(maximum_spliting), Generator(bounding_box), rng(rng){
                int width = bounding_box.get_width();
                int height = bounding_box.get_height();
                
                assert(minimal_split_size >= 2 * minimal_room_size + 4 * bounding_box_padding);

                grid = std::make_shared<Grid>(width, height);
            }

    void run(Scene &scene) override;
private:
    bool can_be_splited(const BoundingBox2i& bounding_box);
    bool can_be_splited_vertically(const BoundingBox2i& bounding_box);
    bool can_be_splited_horizontally(const BoundingBox2i& bounding_box);
    bool get_split_orientation(const BoundingBox2i& bounding_box);
    BoundingBox2i generate_room(const BoundingBox2i& bounding_box, Scene& scene);
    std::pair<BoundingBox2i, BoundingBox2i> calculate_new_bounding_boxes(const BoundingBox2i& bounding_box);
    std::vector<BoundingBox2i> split_space(const BoundingBox2i& bounding_box, Scene& scene);
    std::pair<BoundingBox2i, BoundingBox2i> find_closest_rooms(const std::vector<BoundingBox2i>& first, const std::vector<BoundingBox2i>& second);
};



