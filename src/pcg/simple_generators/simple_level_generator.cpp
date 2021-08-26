#pragma once
#include <glog/logging.h>
#include "src/pcg/simple_generators/simple_level_generator.h"
#include "src/pcg/simple_generators/simple_room_generator.h"
#include "src/pcg/simple_generators/simple_corridor_generator.h"

void SimpleLevelGenerator::run(Scene &scene) {
    DLOG(INFO) << "SimpleLevelGenerator running";

    float room_width = bounding_box.get_width() / 4;
    float room_height = bounding_box.get_height() / 4;
    float corridor_length = bounding_box.get_width() / 3;

    BoundingBox left_room_box = BoundingBox(
            bounding_box.get_middle().shifted_by(-corridor_length / 2 - room_width, -room_height / 2),
            bounding_box.get_middle().shifted_by(-corridor_length / 2, room_height / 2));
    SimpleRoomGenerator left_room_generator(left_room_box);
    left_room_generator.run(scene);

    BoundingBox right_room_box = BoundingBox(
            bounding_box.get_middle().shifted_by(corridor_length / 2, -room_height / 2),
            bounding_box.get_middle().shifted_by(corridor_length / 2 + room_width, room_height / 2));
    SimpleRoomGenerator right_room_generator(right_room_box);
    right_room_generator.run(scene);

    BoundingBox corridor_box = BoundingBox(
                left_room_box.get_top_right(),
                right_room_box.get_bottom_left());
    SimpleCorridorGenerator corridor_generator(corridor_box, SimpleCorridorAlignment::Horizontal);
    corridor_generator.run(scene);

    DLOG(INFO) << "SimpleLevelGenerator finished";
}
