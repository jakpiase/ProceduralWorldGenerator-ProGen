#include "SimpleLevelGenerator.h"
#include "SimpleRoomGenerator.h"

void SimpleLevelGenerator::run(Scene &scene) {
    float room_width = boundingBox.getWidth() / 4;
    float room_height = boundingBox.getHeight() / 4;
    float corridor_length = boundingBox.getWidth() / 3;

    BoundingBox leftRoomBox = BoundingBox(
            boundingBox.getMiddle().move(-corridor_length / 2 - room_width, -room_height / 2),
            boundingBox.getMiddle().move(-corridor_length / 2, room_height / 2));
    SimpleRoomGenerator leftRoomGenerator(leftRoomBox);
    leftRoomGenerator.run(scene);

    BoundingBox rightRoomBox = BoundingBox(
            boundingBox.getMiddle().move(corridor_length / 2, -room_height / 2),
            boundingBox.getMiddle().move(corridor_length / 2 + room_width, room_height / 2));
    SimpleRoomGenerator rightRoomGenerator(rightRoomBox);
    rightRoomGenerator.run(scene);

    //Skipping generating a corridor for now
}
