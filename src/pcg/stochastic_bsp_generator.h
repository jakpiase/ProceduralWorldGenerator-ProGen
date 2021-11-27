#pragma once

#include <utility>
#include <sstream>
#include "src/core/scene.h"
#include "src/core/entity.h"
#include "src/pcg/simple_generators/simple_room_generator.h"
#include "src/pcg/corridor_generator.h"
#include "src/pcg/grid.h"

class StochasticBSPGenerator : public Generator {
    //static constexpr float MAX_PROPORTION = 3.5f;
    //static constexpr float MIN_PROPORTION = 1.0f / MAX_PROPORTION;
    static constexpr float ROOM_PROPORTION = 3.2f;
    const int MINIMAL_CHUNK_SIZE = 13;
    const int CHUNK_PADDING = 2;
    const int MINIMAL_ROOM_SIZE = 6;
    //const int MAXIMAL_ROOM_SIZE = 12;

    const bool maximum_splitting;
    std::shared_ptr<Grid> grid;
    RandomNumberGenerator& rng;
public:
    // MINIMAL_CHUNK_SIZE - the higher the value, the less room will be generated
    // CHUNK_PADDING - room padding from split bounding box
    // MINIMAL_ROOM_SIZE - smallest possible value for width and height of generated room
    // MAXIMAL_ROOM_SIZE - highest possible value for width and height of generated room
    StochasticBSPGenerator(const BoundingBox2i& bounding_box, RandomNumberGenerator& rng,
                                                    bool maximum_spliting = false) : maximum_splitting(maximum_spliting),
                                                                                    Generator(bounding_box), rng(rng) {
        int width = bounding_box.get_width();
        int height = bounding_box.get_height();

        assert(MINIMAL_CHUNK_SIZE >= MINIMAL_ROOM_SIZE + 2 * CHUNK_PADDING);

        grid = std::make_shared<Grid>(width, height);
    }

    void run(Scene& scene) override;

private:
    bool can_be_split(const BoundingBox2i& bounding_box);

    bool can_be_split_vertically(const BoundingBox2i& bounding_box);

    bool can_be_split_horizontally(const BoundingBox2i& bounding_box);

    bool get_split_orientation(const BoundingBox2i& bounding_box);

    void generate_room(const BoundingBox2i& box);

    std::pair<BoundingBox2i, BoundingBox2i> calculate_new_bounding_boxes(const BoundingBox2i& box);

    void split_space(const BoundingBox2i& bounding_box);

    void connect_spaces_with_corridor(const BoundingBox2i& a, const BoundingBox2i& b);

    std::pair<BoundingBox2i, BoundingBox2i>
    find_closest_rooms(const std::vector<BoundingBox2i>& first, const std::vector<BoundingBox2i>& second);
};



