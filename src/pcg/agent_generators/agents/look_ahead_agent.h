#pragma once

#include "src/pcg/utils/direction.h"
#include "src/core/scene.h"
#include "src/pcg/agent_generators/agents/agent.h"

class LookAheadAgent : public Agent {
    const int MIN_ROOM_SIZE = 5;
    const int MAX_ROOM_SIZE = 11;
    const int MIN_CORRIDOR_LENGTH = 7;
    const int MAX_CORRIDOR_LENGTH = 16;

    Point2i position;
    std::vector<BoundingBox2i> rooms_buffer;
    std::vector<BoundingBox2i> corridors_buffer;
    std::vector<std::pair<BoundingBox2i, GridElement>> areas_to_place;

public:
    void run(Scene& scene, Grid& grid, RandomNumberGenerator& rng) override;

private:
    bool try_to_place_room(Scene& scene, Grid& grid);
    bool can_place_room(Grid& grid, BoundingBox2i corridor_box);
    void place_room(Scene& scene, Grid& grid, BoundingBox2i room_box);
    bool can_place_corridor(Grid& grid, BoundingBox2i corridor_box);
    void place_corridor(Scene& scene, Grid& grid, BoundingBox2i corridor_box, Point2i new_position);
    bool try_to_place_corridor(Scene& scene, Grid& grid);

    void flush_rooms_buffer(Scene& scene, Grid& grid);
    void flush_corridors_buffer(Scene& scene, Grid& grid);
    void finish(Scene& scene, Grid& grid);

    std::pair<BoundingBox2i, Point2i> get_corridor_box_with_updated_position(int length, Direction direction);
    Point2i get_starting_position(const Grid& grid, RandomNumberGenerator& rng) const;
};



