#include <sstream>
#include "SimpleRoomGenerator.h"
#include "core/Scene.h"
#include "core/Entity.h"
#include "core/components/DescriptionComponent.h"


void SimpleRoomGenerator::run(Scene &scene) {
    std::stringstream floor_description_stream;
    floor_description_stream << "Floor from " << boundingBox.get_top_left() << " to " << boundingBox.get_bottom_right();
    Entity floor = scene.create_entity();
    floor.add_component<DescriptionComponent>(floor_description_stream.str());

    std::stringstream right_wall_description_stream;
    right_wall_description_stream << "Wall from " << boundingBox.get_top_right() << " to "
                                  << boundingBox.get_bottom_right();
    Entity rightWall = scene.create_entity();
    rightWall.add_component<DescriptionComponent>(right_wall_description_stream.str());
}
