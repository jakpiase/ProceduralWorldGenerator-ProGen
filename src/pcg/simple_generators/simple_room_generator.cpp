#pragma once
#include <sstream>
#include <src/core/components/graphics_component.h>
#include "simple_room_generator.h"
#include "src/core/scene.h"
#include "src/core/entity.h"
#include "src/core/components/description_component.h"
#include "src/core/components/transformation_component.h"


void SimpleRoomGenerator::run(Scene &scene) {
    DLOG(INFO) << "SimpleRoomGenerator running";

    std::stringstream floor_description_stream;
    floor_description_stream << "Floor from " << bounding_box.get_top_left() << " to " << bounding_box.get_bottom_right();
    Entity floor = scene.create_entity();
    floor.add_component<DescriptionComponent>(floor_description_stream.str());
    floor.add_component<TransformationComponent>(bounding_box.get_top_left());
    floor.add_component<GraphicsComponent>(Colors::Red, Dimensions2i(bounding_box.get_width(), bounding_box.get_height()));

    std::stringstream right_wall_description_stream;
    right_wall_description_stream << "Wall from " << bounding_box.get_top_right() << " to "
                                  << bounding_box.get_bottom_right();
    Entity rightWall = scene.create_entity();
    rightWall.add_component<DescriptionComponent>(right_wall_description_stream.str());


    DLOG(INFO) << "SimpleRoomGenerator finished";
}
