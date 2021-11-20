#pragma once
#include "src/pcg/utils/direction.h"
#include "src/core/scene.h"
#include "src/pcg/agent_generators/agents/agent.h"

class LookAheadAgent : public Agent {
    const int MIN_ROOM_SIZE = 4;
    const int MAX_ROOM_SIZE = 8;
    const int MIN_CORRIDOR_LENGTH = 10;
    const int MAX_CORRIDOR_LENGTH = 17;
    const int MAX_CORRIDOR_SEEK_TIME = 3;

    Point2i position;
    std::vector<BoundingBox2i> rooms_buffer;
    std::vector<BoundingBox2i> corridors_buffer;

public:
    void run(Scene& scene, Grid& grid, RandomNumberGenerator& rng) override;

protected:
    void perform_generation(Scene& scene, Grid& grid, RandomNumberGenerator& rng);
    bool try_to_place_room(Scene &scene, Grid &grid, RandomNumberGenerator &rng);
    bool can_place_room(Grid& grid, BoundingBox2i room_box);
    virtual void place_room(Scene& scene, Grid& grid, BoundingBox2i room_box, RandomNumberGenerator& rng);
    virtual bool can_place_corridor(Grid& grid, BoundingBox2i corridor_box, Point2i corridor_end);
    void place_corridor(Scene& scene, Grid& grid, BoundingBox2i corridor_box, Point2i new_position);
    bool try_to_place_corridor(Scene& scene, Grid& grid, RandomNumberGenerator& rng);

    void flush_rooms_buffer(Scene& scene, Grid& grid);
    void flush_corridors_buffer(Scene& scene, Grid& grid);
    void finish(Scene& scene, Grid& grid);

    std::pair<BoundingBox2i, Point2i> get_corridor_box_with_updated_position(int length, Direction direction);

    void set_starting_position(const Grid& grid, RandomNumberGenerator& rng);
    [[nodiscard]] Point2i get_current_position() const;
    void set_current_position(const Point2i& new_position);
    [[nodiscard]] std::vector<BoundingBox2i>& get_corridors_buffer();
};



