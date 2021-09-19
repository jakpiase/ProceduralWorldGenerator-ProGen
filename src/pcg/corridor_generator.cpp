#include <sstream>
#include <cassert>
#include "src/core/components/graphics_component.h"
#include "src/core/components/transformation_component.h"
#include "src/core/components/description_component.h"
#include "src/core/scene.h"
#include "src/core/entity.h"
#include "src/pcg/corridor_generator.h"

void CorridorGenerator::run(Scene& scene) {
    DLOG(INFO) << "CorridorGenerator running";

    const auto corridor_boxes = calculate_corridor_boxes();
    
    for(const auto& corridor_box : corridor_boxes) {
        Entity corridor = scene.create_entity();
        corridor.add_component<TransformationComponent>(corridor_box.get_top_left());
        corridor.add_component<GraphicsComponent>(Colors::Blue, corridor_box.get_dimensions().cast<int>());
    }

    DLOG(INFO) << "CorridorGenerator finished";
}

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
    const auto first_middle = first_room.get_middle();
    const auto second_middle = second_room.get_middle();

    const std::tuple<Point, Point, bool> corridor_characteristics = calculate_corridor_end_points_and_alignment();

    const Point first_connecting_point(std::get<0>(corridor_characteristics));
    const Point fourth_connecting_point(std::get<1>(corridor_characteristics));
    const bool horizontal_corridor(std::get<2>(corridor_characteristics));

    std::vector<BoundingBox> corridor_boxes;
    corridor_boxes.reserve(3);

    generate_corridor_boxes(corridor_boxes, first_connecting_point, fourth_connecting_point, horizontal_corridor);

    return corridor_boxes;
}

//returns first and last corridor points and alignment(true if horizontal)
std::tuple<Point, Point, bool> CorridorGenerator::calculate_corridor_end_points_and_alignment() {
    Point first_middle = first_room.get_middle();
    Point second_middle = second_room.get_middle();

    Point first_connecting_point(0, 0);
    Point fourth_connecting_point(0, 0);

    bool horizontal_corridor = true;
    if (Point::is_vertical_distance_bigger(first_middle, second_middle)) {
        horizontal_corridor = false;
        if (second_middle.is_above(first_middle)) {
            fourth_connecting_point = first_middle.shifted_by(0, -first_room.get_height() / 2);
            first_connecting_point = second_middle.shifted_by(0, second_room.get_height() / 2);
        } else {
            first_connecting_point = first_middle.shifted_by(0, first_room.get_height() / 2);
            fourth_connecting_point = second_middle.shifted_by(0, -second_room.get_height() / 2);            
        }
    } else {
        if (second_middle.is_on_left(first_middle)) {
            fourth_connecting_point = first_middle.shifted_by(-first_room.get_width() / 2, 0);
            first_connecting_point = second_middle.shifted_by(second_room.get_width() / 2, 0);
        } else {
            first_connecting_point = first_middle.shifted_by(first_room.get_width() / 2, 0);
            fourth_connecting_point = second_middle.shifted_by(-second_room.get_width() / 2, 0);            
        }
    }

    return std::tuple<Point, Point, bool>(first_connecting_point, fourth_connecting_point, horizontal_corridor);
}

void CorridorGenerator::generate_corridor_boxes(std::vector<BoundingBox>& corridor_boxes, const Point& first_connecting_point,
                                                const Point& fourth_connecting_point, bool horizontal_corridor) {

    const Point midpoint = Point::midpoint(first_connecting_point, fourth_connecting_point);
    Point second_connecting_point(0, 0);
    Point third_connecting_point(0, 0);

    if (horizontal_corridor) {
        second_connecting_point = Point(midpoint.x, first_connecting_point.y);
        third_connecting_point = Point(midpoint.x, fourth_connecting_point.y);

        corridor_boxes.emplace_back(first_connecting_point.shifted_by(0, -CORRIDOR_WIDTH/2), second_connecting_point.shifted_by(0, CORRIDOR_WIDTH/2));

        if(midpoint.is_above(first_connecting_point))
            corridor_boxes.emplace_back(third_connecting_point.shifted_by(-CORRIDOR_WIDTH/2, -CORRIDOR_WIDTH/2), second_connecting_point.shifted_by(CORRIDOR_WIDTH/2, CORRIDOR_WIDTH/2));
        else
            corridor_boxes.emplace_back(second_connecting_point.shifted_by(-CORRIDOR_WIDTH/2, -CORRIDOR_WIDTH/2), third_connecting_point.shifted_by(CORRIDOR_WIDTH/2, CORRIDOR_WIDTH/2));

        corridor_boxes.emplace_back(third_connecting_point.shifted_by(-CORRIDOR_WIDTH/2, -CORRIDOR_WIDTH/2), fourth_connecting_point.shifted_by(0, CORRIDOR_WIDTH/2));
            
    } else {
        second_connecting_point = Point(first_connecting_point.x, midpoint.y);
        third_connecting_point = Point(fourth_connecting_point.x, midpoint.y);

        corridor_boxes.emplace_back(first_connecting_point.shifted_by(-CORRIDOR_WIDTH/2, 0), second_connecting_point.shifted_by(CORRIDOR_WIDTH/2, 0));

        if(midpoint.is_on_left(first_connecting_point))
            corridor_boxes.emplace_back(third_connecting_point.shifted_by(-CORRIDOR_WIDTH/2, -CORRIDOR_WIDTH/2), second_connecting_point.shifted_by(CORRIDOR_WIDTH/2, CORRIDOR_WIDTH/2));
        else
            corridor_boxes.emplace_back(second_connecting_point.shifted_by(-CORRIDOR_WIDTH/2, -CORRIDOR_WIDTH/2), third_connecting_point.shifted_by(CORRIDOR_WIDTH/2, CORRIDOR_WIDTH/2));
    
        corridor_boxes.emplace_back(third_connecting_point.shifted_by(-CORRIDOR_WIDTH/2, 0), fourth_connecting_point.shifted_by(CORRIDOR_WIDTH/2, 0));
    }
}
