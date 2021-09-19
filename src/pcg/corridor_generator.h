#pragma once
#include <tuple>
#include "src/pcg/generator.h"
#include "src/core/common/bounding_box.h"

class CorridorGenerator : public Generator {
    static constexpr float CORRIDOR_WIDTH = 10.0;
    const BoundingBox first_room, second_room;

public:
    CorridorGenerator(const BoundingBox& first_room, const BoundingBox& second_room)
        : first_room(first_room), second_room(second_room), Generator(BoundingBox(Point(0, 0), Point(0, 0))) {};

    void run(Scene& scene) override;

private:
    std::vector<BoundingBox> calculate_corridor_boxes();
    std::tuple<Point, Point, bool> calculate_corridor_end_points_and_alignment();
    void generate_corridor_boxes(std::vector<BoundingBox>& corridor_boxes, const Point& first_connecting_point,
                                 const Point& fourth_connecting_point, bool horizontal_corridor);
};
