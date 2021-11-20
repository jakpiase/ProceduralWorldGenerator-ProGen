#pragma once
#include <vector>
#include "src/pcg/agent_generators/agents/look_ahead/look_ahead_agent.h"

class RecurringLookAheadAgent : public LookAheadAgent {
    const int RECURSE_CHANGE_INCREASE_PER_ROOM = 20;
    const int INITIAL_RECURSE_CHANCE = 0;
    const bool ALLOW_MULTIPLE_RETURNS = true;
    const unsigned int NUMBER_OF_GENERATIONS_ALLOWED = 100;

    unsigned int recurse_chance = INITIAL_RECURSE_CHANCE;
    std::vector<Point2i> visited_rooms_positions;
    std::unique_ptr<BoundingBox2i> room_excluded_from_corridor_collision;
public:
    void run(Scene& scene, Grid& grid, RandomNumberGenerator& rng) override;

protected:
    void place_room(Scene& scene, Grid& grid, BoundingBox2i room_box, RandomNumberGenerator& rng) override;
    bool can_place_corridor(Grid& grid, BoundingBox2i corridor_box, Point2i corridor_end) override;

private:
    void perform_recursive_move(Scene& scene, Grid& grid, RandomNumberGenerator& rng);
    void mark_current_position_as_visited();
    void go_to_previous_position(const Grid& grid, RandomNumberGenerator& rng);
    Point2i pop_previous_position_at_index(unsigned int index);
};



