#pragma once
#include "src/pcg/utils/direction.h"
#include "src/core/scene.h"
#include "src/pcg/agent_generators/agents/agent.h"
#include "src/pcg/bbox_grid_wrapper.h"

class LookAheadAgent : public Agent {
//    const int MIN_ROOM_SIZE = 6;
//    const int MAX_ROOM_SIZE = 11;
//    const int MIN_CORRIDOR_LENGTH = 12;
//    const int MAX_CORRIDOR_LENGTH = 18;

    const int MIN_ROOM_SIZE = 2;
    const int MAX_ROOM_SIZE = 4;
    const int MIN_CORRIDOR_LENGTH = 5;
    const int MAX_CORRIDOR_LENGTH = 7;
    const int MAX_CORRIDOR_SEEK_TIME = 4;

    Point2i position;
    int corridor_seek_time = 0;
    std::vector<BoundingBox2i> rooms_buffer;
    std::vector<BoundingBox2i> corridors_buffer;

public:
    void run(Scene& scene, Grid& grid, RandomNumberGenerator& rng) override;

private:
    bool try_to_place_room(Scene &scene, Grid &grid, RandomNumberGenerator &rng);
    bool can_place_room(Grid& grid, BoundingBox2i room_box);
    void place_room(Scene& scene, Grid& grid, BoundingBox2i room_box);
    bool can_place_corridor(Grid& grid, BoundingBox2i corridor_box, Point2i corridor_end);
    void place_corridor(Scene& scene, Grid& grid, BoundingBox2i corridor_box, Point2i new_position);
    bool try_to_place_corridor(Scene& scene, Grid& grid, RandomNumberGenerator& rng);

    void flush_rooms_buffer(Scene& scene, Grid& grid);
    void flush_corridors_buffer(Scene& scene, Grid& grid);
    void finish(Scene& scene, Grid& grid);

    std::pair<BoundingBox2i, Point2i> get_corridor_box_with_updated_position(int length, Direction direction);
    Point2i get_starting_position(const Grid& grid, RandomNumberGenerator& rng) const;

    bool can_place_room(BBoxGridWrapper& bbox_grid, BoundingBox2i room_box);

    bool try_to_place_room(Scene &scene, BBoxGridWrapper &bbox_grid, RandomNumberGenerator &rng);

    void flush_corridors_buffer(Scene &scene, BBoxGridWrapper &bbox_grid);

    void place_room(Scene &scene, BBoxGridWrapper &bbox_grid, BoundingBox2i room_box);
};



