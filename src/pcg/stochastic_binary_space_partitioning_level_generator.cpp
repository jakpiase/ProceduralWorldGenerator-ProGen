#include "src/pcg/stochastic_binary_space_partitioning_level_generator.h"
#include <iostream>

void StochasticBinarySpacePartitioningLevelGenerator::run(Scene &scene) {
    DLOG(INFO) << "StochasticBinarySpacePartitioningLevelGenerator running";

    split_space(bounding_box, scene);

    DLOG(INFO) << "StochasticBinarySpacePartitioningLevelGenerator finished";
}

bool StochasticBinarySpacePartitioningLevelGenerator::can_be_splited(const BoundingBox& bounding_box) {
    if (maximum_spliting)
        return can_be_splited_horizontally(bounding_box) || can_be_splited_vertically(bounding_box);
    else
        return can_be_splited_horizontally(bounding_box) && can_be_splited_vertically(bounding_box);
}

bool StochasticBinarySpacePartitioningLevelGenerator::can_be_splited_vertically(const BoundingBox& bounding_box) {
    return bounding_box.get_width() > 2 * minimal_split_size;
}

bool StochasticBinarySpacePartitioningLevelGenerator::can_be_splited_horizontally(const BoundingBox& bounding_box) {
    return bounding_box.get_height() > 2 * minimal_split_size;
}

// returns true if horizontal
bool StochasticBinarySpacePartitioningLevelGenerator::get_split_orientation(const BoundingBox& bounding_box, RandomNumberGenerator* random_generator) {
    if (maximum_spliting) {
        if (can_be_splited_horizontally(bounding_box) && can_be_splited_vertically(bounding_box))
            return random_generator->random_bool();
        else
            return can_be_splited_horizontally(bounding_box);
    } else {
        return random_generator->random_bool();
    }
}

BoundingBox StochasticBinarySpacePartitioningLevelGenerator::generate_room(const BoundingBox& bounding_box, Scene& scene) {
    auto& random_generator = scene.get_random_generator();

    float room_width, room_height;

    if (bounding_box.get_width() > bounding_box.get_height()) {
        room_height = random_generator.random(minimal_room_size, bounding_box.get_height() - 2 * bounding_box_padding);

        int width_upper_bound = std::min(MAX_PROPORTION * room_height, bounding_box.get_width());
        int width_lower_bound = std::max<int>(MIN_PROPORTION * room_height, minimal_room_size);
        room_width = random_generator.random(width_lower_bound, width_upper_bound - 2 * bounding_box_padding);
    } else {
        room_width = random_generator.random(minimal_room_size, bounding_box.get_width() - 2 * bounding_box_padding);

        int height_upper_bound = std::min(MAX_PROPORTION * room_width, bounding_box.get_height());
        int height_lower_bound = std::max<int>(MIN_PROPORTION * room_width, minimal_room_size);
        room_height = random_generator.random(height_lower_bound, height_upper_bound - 2 * bounding_box_padding);
    }

    float room_x = bounding_box.get_top_left().x + bounding_box_padding + random_generator.random(static_cast<int>(bounding_box.get_width() - room_width - 2 * bounding_box_padding));
    float room_y = bounding_box.get_top_left().y + bounding_box_padding + random_generator.random(static_cast<int>(bounding_box.get_height() - room_height - 2 * bounding_box_padding));

    BoundingBox room_bounding_box(Point(room_x, room_y), Point(room_x + room_width, room_y + room_height));
    SimpleRoomGenerator room_generator(room_bounding_box);
    room_generator.run(scene);

    return room_bounding_box;
}

std::pair<BoundingBox, BoundingBox> StochasticBinarySpacePartitioningLevelGenerator::calculate_new_bounding_boxes(const BoundingBox& bounding_box, RandomNumberGenerator* random_generator) {
    Point first_top_left = bounding_box.get_top_left();
    Point second_bottom_right = bounding_box.get_bottom_right();

    bool horizontal = get_split_orientation(bounding_box, random_generator);

    // minimal split length/width constraint ensures that room layout will be spread out realisticly
    // f.e. instead of split <0, DIMENSION_SIZE) we have <minimal_split_size, DIMENSION_SIZE - minimal_split_size)
    Point first_bottom_right(0, 0), second_top_left(0, 0);
    if (horizontal) {
        int split_height = minimal_split_size + bounding_box.get_top_left().y + random_generator->random(static_cast<int>(bounding_box.get_height() - 2 * minimal_split_size));
    
        first_bottom_right = Point(bounding_box.get_bottom_right().x, split_height);
        second_top_left = Point(bounding_box.get_top_left().x, split_height);
    } else {
        int split_width = minimal_split_size + bounding_box.get_top_left().x + random_generator->random(static_cast<int>(bounding_box.get_width() - 2 * minimal_split_size));
            
        first_bottom_right = Point(split_width, bounding_box.get_bottom_right().y);
        second_top_left = Point(split_width, bounding_box.get_top_left().y);            
    }

    return std::pair<BoundingBox, BoundingBox>{{first_top_left, first_bottom_right}, {second_top_left, second_bottom_right}};
}

// Split divides bounding_box into two smaller ones, either by vertical or horizontal cut
// no matter which kind of split is applied, "first" created bounding box will be 
// leftmost/topmost and "second" will be rightmost/bottommost
//
// Example:
// dividing ((10, 30), (20, 40)) bounding box by a perfectly symetric vertical cut will result
// in first:((10, 30), (15, 40)) second:((15, 30), (20, 40)) 

std::vector<BoundingBox> StochasticBinarySpacePartitioningLevelGenerator::split_space(const BoundingBox& bounding_box, Scene& scene) {
    auto& random_generator = scene.get_random_generator();

    if (can_be_splited(bounding_box)) {
        std::pair<BoundingBox, BoundingBox> new_bounding_boxes = calculate_new_bounding_boxes(bounding_box, &random_generator);

        DLOG(INFO) << "Spliting surface from " << bounding_box << " into " << new_bounding_boxes.first << " and " << new_bounding_boxes.second;
        auto first_rooms = split_space(new_bounding_boxes.first, scene);
        auto second_rooms = split_space(new_bounding_boxes.second, scene);

        auto closest_rooms = find_closest_rooms(first_rooms, second_rooms);
        auto corridor_generator = CorridorGenerator(closest_rooms.first, closest_rooms.second);
        DLOG(INFO) << "Corridor between: " << closest_rooms.first << " and " << closest_rooms.second << std::endl;
        corridor_generator.run(scene);

        // combine both subgroups into one big group
        first_rooms.insert(first_rooms.end(), second_rooms.begin(), second_rooms.end());
        return first_rooms;
    } else {
        return {generate_room(bounding_box, scene)};
    }
}

std::pair<BoundingBox, BoundingBox> StochasticBinarySpacePartitioningLevelGenerator::find_closest_rooms(const std::vector<BoundingBox>& first, const std::vector<BoundingBox>& second) {
    
    BoundingBox result_first = first[0];
    BoundingBox result_second = second[0];
    int first_idx = 0;
    int second_idx = 0;

    int closest_distace = BoundingBox::manhattan_distance(result_first, result_second);

    for(int i=0; i<first.size(); ++i) {
        for(int j=0; j<second.size(); ++j) {
            int distance = BoundingBox::manhattan_distance(first[i], second[j]);
            if(closest_distace > distance) {
                closest_distace = distance;
                first_idx = i;
                second_idx = j;
            }
        }
    }
    return std::pair<BoundingBox, BoundingBox>(first[first_idx], second[second_idx]);
}
