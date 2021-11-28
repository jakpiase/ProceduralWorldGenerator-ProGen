#include <glog/logging.h>
#include "src/pcg/simple_generators/simple_level_generator.h"
#include "src/pcg/simple_generators/simple_room_generator.h"
#include "src/pcg/simple_generators/simple_corridor_generator.h"

void SimpleLevelGenerator::run(Scene &scene) {
    DLOG(INFO) << "SimpleLevelGenerator running";

    const float room_width = bounding_box.get_width() / 4;
    const float room_height = bounding_box.get_height() / 4;
    const float corridor_length = bounding_box.get_width() / 3;

    BoundingBox2i left_room_box = BoundingBox2i(
            bounding_box.get_middle().shifted_by(-corridor_length / 2 - room_width, -room_height / 2),
            bounding_box.get_middle().shifted_by(-corridor_length / 2, room_height / 2));
    SimpleRoomGenerator left_room_generator(left_room_box);
    left_room_generator.run(scene);

    BoundingBox2i right_room_box = BoundingBox2i(
            bounding_box.get_middle().shifted_by(corridor_length / 2, -room_height / 2),
            bounding_box.get_middle().shifted_by(corridor_length / 2 + room_width, room_height / 2));
    SimpleRoomGenerator right_room_generator(right_room_box);
    right_room_generator.run(scene);

    BoundingBox2i corridor_box = BoundingBox2i(
                left_room_box.get_top_right(),
                right_room_box.get_bottom_left());
    SimpleCorridorGenerator corridor_generator(corridor_box, SimpleCorridorAlignment::Horizontal);
    corridor_generator.run(scene);

    DLOG(INFO) << "SimpleLevelGenerator finished";
}
