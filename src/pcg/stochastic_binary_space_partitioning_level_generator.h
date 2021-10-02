#pragma once

#include <utility>
#include <sstream>
#include "src/core/scene.h"
#include "src/core/entity.h"
#include "src/pcg/simple_generators/simple_room_generator.h"
#include "src/pcg/corridor_generator.h"
#include "src/pcg/grid.h"

class StochasticBinarySpacePartitioningLevelGenerator : public Generator {
    std::shared_ptr<Grid> grid;
    static constexpr float MAX_PROPORTION = 3.5f;
    static constexpr float MIN_PROPORTION = 1.0f/MAX_PROPORTION;
    const int minimal_split_size;
    const int minimal_room_size;
    const int maximal_room_size;
    const int bounding_box_padding;
    const bool maximum_spliting;
public:
    explicit StochasticBinarySpacePartitioningLevelGenerator(const BoundingBox2i& bounding_box, bool maximum_spliting = true)
            : minimal_split_size(130), bounding_box_padding(5), minimal_room_size(40), maximal_room_size(80),
              maximum_spliting(maximum_spliting), Generator(bounding_box){
                int width = bounding_box.get_width();
                int height = bounding_box.get_height();
                
                assert(minimal_split_size >= 2 * minimal_room_size + 4 * bounding_box_padding);

                assert(bounding_box_padding % Grid::ELEMENT_SIZE == 0);
                assert(minimal_room_size % Grid::ELEMENT_SIZE == 0);
                assert(width % Grid::ELEMENT_SIZE == 0);
                assert(height % Grid::ELEMENT_SIZE == 0);

                grid = std::make_shared<Grid>(width / Grid::ELEMENT_SIZE, height / Grid::ELEMENT_SIZE);
            }

    void run(Scene &scene) override;
private:
    bool can_be_splited(const BoundingBox2i& bounding_box);
    bool can_be_splited_vertically(const BoundingBox2i& bounding_box);
    bool can_be_splited_horizontally(const BoundingBox2i& bounding_box);
    bool get_split_orientation(const BoundingBox2i& bounding_box, RandomNumberGenerator* random_generator);
    BoundingBox2i generate_room(const BoundingBox2i& bounding_box, Scene& scene);
    std::pair<BoundingBox2i, BoundingBox2i> calculate_new_bounding_boxes(const BoundingBox2i& bounding_box, RandomNumberGenerator* random_generator);
    std::vector<BoundingBox2i> split_space(const BoundingBox2i& bounding_box, Scene& scene);
    std::pair<BoundingBox2i, BoundingBox2i> find_closest_rooms(const std::vector<BoundingBox2i>& first, const std::vector<BoundingBox2i>& second);
};



