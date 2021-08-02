#include "SimpleLevelGenerator.h"
#include "SimpleRoomGenerator.h"
#include <glog/logging.h>

void SimpleLevelGenerator::run(Scene &scene) {
    DLOG(INFO) << "SimpleLevelGenerator running";

    float room_width = bounding_box.get_width() / 4;
    float room_height = bounding_box.get_height() / 4;
    float corridor_length = bounding_box.get_width() / 3;

    BoundingBox leftRoomBox = BoundingBox(
            bounding_box.get_middle().shifted_by(-corridor_length / 2 - room_width, -room_height / 2),
            bounding_box.get_middle().shifted_by(-corridor_length / 2, room_height / 2));
    SimpleRoomGenerator leftRoomGenerator(leftRoomBox);
    leftRoomGenerator.run(scene);

    BoundingBox rightRoomBox = BoundingBox(
            bounding_box.get_middle().shifted_by(corridor_length / 2, -room_height / 2),
            bounding_box.get_middle().shifted_by(corridor_length / 2 + room_width, room_height / 2));
    SimpleRoomGenerator rightRoomGenerator(rightRoomBox);
    rightRoomGenerator.run(scene);

    //Skipping generating a corridor for now
    DLOG(INFO) << "SimpleLevelGenerator finished";
}
