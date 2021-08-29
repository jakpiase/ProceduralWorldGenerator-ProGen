#include <sstream>
#include "src/pcg/simple_room_generator.h"


void SimpleRoomGenerator::run(Scene &scene) {
    DLOG(INFO) << "SimpleRoomGenerator running";

    std::stringstream floor_description_stream;
    floor_description_stream << "Floor from " << bounding_box.get_top_left() << " to " << bounding_box.get_bottom_right();
    Entity floor = scene.create_entity();
    floor.add_component<DescriptionComponent>(floor_description_stream.str());
    floor.add_component<PhysicsComponent>(bounding_box);

    std::stringstream top_wall_description_stream;
    top_wall_description_stream << "Wall from " << bounding_box.get_top_right() << " to "
                                  << bounding_box.get_top_left();
    Entity top_wall = scene.create_entity();
    top_wall.add_component<DescriptionComponent>(top_wall_description_stream.str());
    top_wall.add_component<PhysicsComponent>(BoundingBox(bounding_box.get_top_right(), bounding_box.get_top_left()));

    std::stringstream right_wall_description_stream;
    right_wall_description_stream << "Wall from " << bounding_box.get_top_right() << " to "
                                  << bounding_box.get_bottom_right();
    Entity right_wall = scene.create_entity();
    right_wall.add_component<DescriptionComponent>(right_wall_description_stream.str());
    right_wall.add_component<PhysicsComponent>(BoundingBox(bounding_box.get_top_right(), bounding_box.get_bottom_right()));

    std::stringstream bottom_wall_description_stream;
    bottom_wall_description_stream << "Wall from " << bounding_box.get_bottom_left() << " to "
                                  << bounding_box.get_bottom_right();
    Entity bottom_wall = scene.create_entity();
    bottom_wall.add_component<DescriptionComponent>(bottom_wall_description_stream.str());
    bottom_wall.add_component<PhysicsComponent>(BoundingBox(bounding_box.get_bottom_left(), bounding_box.get_bottom_right()));

    std::stringstream left_wall_description_stream;
    left_wall_description_stream << "Wall from " << bounding_box.get_top_left() << " to "
                                  << bounding_box.get_bottom_left();
    Entity left_wall = scene.create_entity();
    left_wall.add_component<DescriptionComponent>(left_wall_description_stream.str());
    left_wall.add_component<PhysicsComponent>(BoundingBox(bounding_box.get_top_left(), bounding_box.get_bottom_left()));


    DLOG(INFO) << "SimpleRoomGenerator finished";
}
