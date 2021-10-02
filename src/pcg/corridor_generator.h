#pragma once
#include <tuple>
#include "src/pcg/generator.h"
#include "src/core/common/bounding_box.h"

class CorridorGenerator : public Generator {
    static constexpr float CORRIDOR_WIDTH = 10.0;
    const BoundingBox2i first_room, second_room;

public:
    CorridorGenerator(const BoundingBox2i& first_room, const BoundingBox2i& second_room)
        : first_room(first_room), second_room(second_room), Generator(BoundingBox(Point2i(0, 0), Point2i(0, 0))) {};

    void run(Scene& scene) override;

private:
    std::vector<BoundingBox2i> calculate_corridor_boxes();
    std::tuple<Point2i, Point2i, bool> calculate_corridor_end_points_and_alignment();
    void generate_corridor_boxes(std::vector<BoundingBox2i>& corridor_boxes, const Point2i& first_connecting_point,
                                 const Point2i& fourth_connecting_point, bool horizontal_corridor);
};
