#include "src/pcg/binary_space_partitioning_level_generator.h"

void BinarySpacePartitioningLevelGenerator::run(Scene &scene) {
    DLOG(INFO) << "BinarySpacePartitioningLevelGenerator running";

    split_space(bounding_box, scene);

    DLOG(INFO) << "BinarySpacePartitioningLevelGenerator finished";
}

bool BinarySpacePartitioningLevelGenerator::can_be_splited(const BoundingBox& bounding_box) {
    return bounding_box.get_width() > 2 * minimal_split_size && bounding_box.get_height() > 2 * minimal_split_size;
}

void BinarySpacePartitioningLevelGenerator::generate_room(const BoundingBox& bounding_box, Scene& scene) {
    auto& random_generator = scene.get_random_generator();

    DLOG(INFO) << "Final bounding box: " << bounding_box;

    float room_width = minimal_room_size + random_generator.random() % static_cast<int>(bounding_box.get_width() * 0.85 - 2 * minimal_room_size);
    float room_height = minimal_room_size + random_generator.random() % static_cast<int>(bounding_box.get_height() * 0.85 - 2 * minimal_room_size);

    float room_x = bounding_box.get_top_left().x + bounding_box_padding + random_generator.random() % static_cast<int>(bounding_box.get_width() - room_width);
    float room_y = bounding_box.get_top_left().y + bounding_box_padding + random_generator.random() % static_cast<int>(bounding_box.get_height() - room_height);


    SimpleRoomGenerator room_generator({{room_x, room_y}, {room_x + room_width, room_y + room_height}});
    room_generator.run(scene);           
}

std::pair<BoundingBox, BoundingBox> BinarySpacePartitioningLevelGenerator::calculate_new_bounding_boxes(const BoundingBox& bounding_box, RandomNumberGenerator* random_generator) {
    Point first_top_left = bounding_box.get_top_left();
    Point second_bottom_right = bounding_box.get_bottom_right();

    bool horizontal = (random_generator->random() & (0x100));
    // minimal split length/width constraint ensures that room layout will be spread out realisticly
    // f.e. instead of split <0, DIMENSION_SIZE) we have <minimal_split_size, DIMENSION_SIZE - minimal_split_size)
    Point first_bottom_right(0, 0), second_top_left(0, 0);
    if (horizontal) {
        int split_height = minimal_split_size + bounding_box.get_top_left().y + random_generator->random() % static_cast<int>(bounding_box.get_height() - 2 * minimal_split_size);
            
        first_bottom_right = Point(bounding_box.get_bottom_right().x, split_height);
        second_top_left = Point(bounding_box.get_top_left().x, split_height);
    } else {
        int split_width = minimal_split_size + bounding_box.get_top_left().x + random_generator->random() % static_cast<int>(bounding_box.get_width() - 2 * minimal_split_size);
            
        first_bottom_right = Point(split_width, bounding_box.get_bottom_right().y);
        second_top_left = Point(split_width, bounding_box.get_top_left().y);            
    }

    return std::pair<BoundingBox, BoundingBox>{{first_top_left, first_bottom_right}, {second_top_left, second_bottom_right}};
}

// split divides bounding_box into two smaller ones, either by vertical or horizontal cut
// no matter which kind of split is applied, "first" created bounding box will be 
// leftmost/topmost and "second" will be rightmost/bottommost
//
// Example:
// dividing ((10, 30), (20, 40)) bounding box by a perfectly symetric vertical cut will result
// in first:((10, 30), (15, 40)) second:((15, 30), (20, 40)) 
void BinarySpacePartitioningLevelGenerator::split_space(const BoundingBox& bounding_box, Scene& scene) {
    auto& random_generator = scene.get_random_generator();

    if (can_be_splited(bounding_box)) {
        std::pair<BoundingBox, BoundingBox> new_bounding_boxes = calculate_new_bounding_boxes(bounding_box, &random_generator);

        DLOG(INFO) << "Spliting surface from " << bounding_box << " into " << new_bounding_boxes.first << " and " << new_bounding_boxes.second;
        split_space(new_bounding_boxes.first, scene);
        split_space(new_bounding_boxes.second, scene);

        //Skipping generating corridors for now
    } else {
        generate_room(bounding_box, scene);
    }
}
