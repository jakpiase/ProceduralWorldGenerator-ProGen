#pragma once
#include <tuple>
#include "src/pcg/generator.h"
#include "src/core/common/bounding_box.h"

class CorridorGenerator : public Generator {
    static constexpr float CORRIDOR_WIDTH = 10.0;
    const BoundingBox2f first_room, second_room;

public:
    CorridorGenerator(const BoundingBox2f& first_room, const BoundingBox2f& second_room)
        : first_room(first_room), second_room(second_room), Generator(BoundingBox(Point2f(0, 0), Point2f(0, 0))) {};

    void run(Scene& scene) override;

private:
    std::vector<BoundingBox2f> calculate_corridor_boxes();
    std::tuple<Point2f, Point2f, bool> calculate_corridor_end_points_and_alignment();
    void generate_corridor_boxes(std::vector<BoundingBox2f>& corridor_boxes, const Point2f& first_connecting_point,
                                 const Point2f& fourth_connecting_point, bool horizontal_corridor);
};
