#pragma once
#include "src/pcg/agent_generators/agents/look_ahead/look_ahead_agent.h"


class CrossCorridorLookAheadAgent : public  LookAheadAgent {
public:
    bool can_place_corridor(Grid& grid, BoundingBox2i corridor_box, Point2i corridor_end) override;
};



