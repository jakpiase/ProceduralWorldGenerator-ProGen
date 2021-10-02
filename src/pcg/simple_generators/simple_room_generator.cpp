#pragma once
#include <sstream>
#include "src/pcg/simple_generators/simple_room_generator.h"

void SimpleRoomGenerator::run(Scene &scene) {
    DLOG(INFO) << "SimpleRoomGenerator running";

    std::stringstream floor_description_stream;
    floor_description_stream << "Floor from " << bounding_box.get_top_left() << " to " << bounding_box.get_bottom_right();
    Entity floor = scene.create_entity();
    floor.add_component<DescriptionComponent>(floor_description_stream.str());
    floor.add_component<PhysicsComponent>(bounding_box);
    floor.add_component<TransformationComponent>(bounding_box.get_top_left());
    floor.add_component<GraphicsComponent>(Colors::Red, Dimensions2i(bounding_box.get_width(), bounding_box.get_height()));

    // Walls are no longer generated in SimpletRoomGenerator 
    // They will be generated based on how corridors and rooms will be placed on grid

    DLOG(INFO) << "SimpleRoomGenerator finished";
}
