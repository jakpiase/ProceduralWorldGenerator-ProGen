#pragma once
#include <sstream>
#include "src/pcg/simple_generators/simple_room_generator.h"

void SimpleRoomGenerator::run(Scene &scene) {
    DLOG(INFO) << "SimpleRoomGenerator running";

    Entity floor = scene.create_entity();
    floor.add_component<PhysicsComponent>(bounding_box);
    floor.add_component<TransformationComponent>(bounding_box.get_top_left());
    floor.add_component<GraphicsComponent>(Colors::Red, Dimensions2i(bounding_box.get_width(), bounding_box.get_height()));

    DLOG(INFO) << "SimpleRoomGenerator finished";
}
