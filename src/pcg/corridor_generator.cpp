#pragma once
#include <sstream>
#include <cassert>
#include "src/core/components/graphics_component.h"
#include "src/core/components/transformation_component.h"
#include "src/core/components/description_component.h"
#include "src/core/scene.h"
#include "src/core/entity.h"
#include "src/pcg/corridor_generator.h"

/*
Corridors are connected using "midpoint" i.e. a point that is exactly between two centres
of the rooms. A corridor always is constructed as 3 entities. Horizontal connection example:

ooo
ooo
oAo
 o
 BoMoC
     o
    oDo
    ooo
    ooo

M - midpoint
A - first_connecting_point
B - second_connecting_point
C - third_connecting_point
D - fourth_connecting_point
*/


std::vector<BoundingBox> CorridorGenerator::calculate_corridor_boxes() {
    auto first_middle = first_room.get_middle();
    auto second_middle = second_room.get_middle();

    Point first_connecting_point(0, 0);
    Point fourth_connecting_point(0, 0);


    bool horizontal_corridor = true;

    if (std::abs(first_middle.x - second_middle.x) < std::abs(first_middle.y - second_middle.y)) {
        horizontal_corridor = false;
        if (first_middle.y > second_middle.y) {
            fourth_connecting_point = first_middle.shifted_by(0, -first_room.get_height() / 2);
            first_connecting_point = second_middle.shifted_by(0, second_room.get_height() / 2);
        } else {
            first_connecting_point = first_middle.shifted_by(0, first_room.get_height() / 2);
            fourth_connecting_point = second_middle.shifted_by(0, -second_room.get_height() / 2);            
        }
    } else {
        if (first_middle.x > second_middle.x) {
            fourth_connecting_point = first_middle.shifted_by(-first_room.get_width() / 2, 0);
            first_connecting_point = second_middle.shifted_by(second_room.get_width() / 2, 0);
        } else {
            first_connecting_point = first_middle.shifted_by(first_room.get_width() / 2, 0);
            fourth_connecting_point = second_middle.shifted_by(-second_room.get_width() / 2, 0);            
        }
    }
            
    Point midpoint((first_connecting_point.x + fourth_connecting_point.x) / 2, (first_connecting_point.y + fourth_connecting_point.y) / 2);
    Point second_connecting_point(0, 0);
    Point third_connecting_point(0, 0);

    std::vector<BoundingBox> corridor_boxes;
    corridor_boxes.reserve(3);

    if (horizontal_corridor) {
        second_connecting_point = Point(midpoint.x, first_connecting_point.y);
        third_connecting_point = Point(midpoint.x, fourth_connecting_point.y);

        corridor_boxes.emplace_back(first_connecting_point.shifted_by(0, -CORRIDOR_WIDTH/2), second_connecting_point.shifted_by(0, CORRIDOR_WIDTH/2));

        if(midpoint.y < first_connecting_point.y)
            corridor_boxes.emplace_back(third_connecting_point.shifted_by(-CORRIDOR_WIDTH/2, -CORRIDOR_WIDTH/2), second_connecting_point.shifted_by(CORRIDOR_WIDTH/2, CORRIDOR_WIDTH/2));
        else
            corridor_boxes.emplace_back(second_connecting_point.shifted_by(-CORRIDOR_WIDTH/2, -CORRIDOR_WIDTH/2), third_connecting_point.shifted_by(CORRIDOR_WIDTH/2, CORRIDOR_WIDTH/2));

        corridor_boxes.emplace_back(third_connecting_point.shifted_by(-CORRIDOR_WIDTH/2, -CORRIDOR_WIDTH/2), fourth_connecting_point.shifted_by(0, CORRIDOR_WIDTH/2));
            
    } else {
        second_connecting_point = Point(first_connecting_point.x, midpoint.y);
        third_connecting_point = Point(fourth_connecting_point.x, midpoint.y);

        corridor_boxes.emplace_back(first_connecting_point.shifted_by(-CORRIDOR_WIDTH/2, 0), second_connecting_point.shifted_by(CORRIDOR_WIDTH/2, 0));

        if(midpoint.x < first_connecting_point.x)
            corridor_boxes.emplace_back(third_connecting_point.shifted_by(-CORRIDOR_WIDTH/2, -CORRIDOR_WIDTH/2), second_connecting_point.shifted_by(CORRIDOR_WIDTH/2, CORRIDOR_WIDTH/2));
        else
            corridor_boxes.emplace_back(second_connecting_point.shifted_by(-CORRIDOR_WIDTH/2, -CORRIDOR_WIDTH/2), third_connecting_point.shifted_by(CORRIDOR_WIDTH/2, CORRIDOR_WIDTH/2));
    
        corridor_boxes.emplace_back(third_connecting_point.shifted_by(-CORRIDOR_WIDTH/2, 0), fourth_connecting_point.shifted_by(CORRIDOR_WIDTH/2, 0));
    }

    return corridor_boxes;
}

void CorridorGenerator::run(Scene& scene) {
    DLOG(INFO) << "CorridorGenerator running";

    bool horizontal_connection;
    const auto corridor_boxes = calculate_corridor_boxes();
    
    for(const auto& corridor_box : corridor_boxes) {
        Entity corridor = scene.create_entity();
        corridor.add_component<TransformationComponent>(corridor_box.get_top_left());
        corridor.add_component<GraphicsComponent>(Colors::Blue, corridor_box.get_dimensions().cast<int>());
    }

    DLOG(INFO) << "CorridorGenerator finished";
}

