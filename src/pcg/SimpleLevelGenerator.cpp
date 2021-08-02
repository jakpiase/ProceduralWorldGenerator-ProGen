#include "SimpleLevelGenerator.h"
#include "SimpleRoomGenerator.h"

void SimpleLevelGenerator::run(Scene &scene) {
    float room_width = boundingBox.get_width() / 4;
    float room_height = boundingBox.get_height() / 4;
    float corridor_length = boundingBox.get_width() / 3;

    BoundingBox leftRoomBox = BoundingBox(
            boundingBox.get_middle().move(-corridor_length / 2 - room_width, -room_height / 2),
            boundingBox.get_middle().move(-corridor_length / 2, room_height / 2));
    SimpleRoomGenerator leftRoomGenerator(leftRoomBox);
    leftRoomGenerator.run(scene);

    BoundingBox rightRoomBox = BoundingBox(
            boundingBox.get_middle().move(corridor_length / 2, -room_height / 2),
            boundingBox.get_middle().move(corridor_length / 2 + room_width, room_height / 2));
    SimpleRoomGenerator rightRoomGenerator(rightRoomBox);
    rightRoomGenerator.run(scene);

    //Skipping generating a corridor for now
}
