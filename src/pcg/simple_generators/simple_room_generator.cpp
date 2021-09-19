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

    std::stringstream top_wall_description_stream;
    top_wall_description_stream << "Wall from " << bounding_box.get_top_right() << " to "
                                  << bounding_box.get_top_left();
    Entity top_wall = scene.create_entity();
    top_wall.add_component<DescriptionComponent>(top_wall_description_stream.str());
    top_wall.add_component<PhysicsComponent>(BoundingBox(bounding_box.get_top_left(), bounding_box.get_top_right()));
    top_wall.add_component<TransformationComponent>(bounding_box.get_top_left());
    top_wall.add_component<GraphicsComponent>(Colors::Red, Dimensions2i(bounding_box.get_width(), 1));

    std::stringstream right_wall_description_stream;
    right_wall_description_stream << "Wall from " << bounding_box.get_top_right() << " to "
                                  << bounding_box.get_bottom_right();
    Entity right_wall = scene.create_entity();
    right_wall.add_component<DescriptionComponent>(right_wall_description_stream.str());
    right_wall.add_component<PhysicsComponent>(BoundingBox(bounding_box.get_top_right(), bounding_box.get_bottom_right()));
    right_wall.add_component<TransformationComponent>(bounding_box.get_top_right());
    right_wall.add_component<GraphicsComponent>(Colors::Red, Dimensions2i(1, bounding_box.get_height()));

    std::stringstream bottom_wall_description_stream;
    bottom_wall_description_stream << "Wall from " << bounding_box.get_bottom_left() << " to "
                                  << bounding_box.get_bottom_right();
    Entity bottom_wall = scene.create_entity();
    bottom_wall.add_component<DescriptionComponent>(bottom_wall_description_stream.str());
    bottom_wall.add_component<PhysicsComponent>(BoundingBox(bounding_box.get_bottom_left(), bounding_box.get_bottom_right()));
    bottom_wall.add_component<TransformationComponent>(bounding_box.get_bottom_left());
    bottom_wall.add_component<GraphicsComponent>(Colors::Red, Dimensions2i(bounding_box.get_width(), 1));

    std::stringstream left_wall_description_stream;
    left_wall_description_stream << "Wall from " << bounding_box.get_top_left() << " to "
                                  << bounding_box.get_bottom_left();
    Entity left_wall = scene.create_entity();
    left_wall.add_component<DescriptionComponent>(left_wall_description_stream.str());
    left_wall.add_component<PhysicsComponent>(BoundingBox(bounding_box.get_top_left(), bounding_box.get_bottom_left()));
    left_wall.add_component<TransformationComponent>(bounding_box.get_top_left());
    left_wall.add_component<GraphicsComponent>(Colors::Red, Dimensions2i(1, bounding_box.get_height()));


    DLOG(INFO) << "SimpleRoomGenerator finished";
}
