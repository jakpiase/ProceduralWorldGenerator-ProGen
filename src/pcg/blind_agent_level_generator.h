#pragma once

#include <utility>
#include "src/pcg/simple_generators/simple_room_generator.h"
#include "src/pcg/corridor_generator.h"

enum class DiggingDirection {
    up,
    right,
    down,
    left,
};

class BlindAgentLevelGenerator : public Generator {
    static constexpr float MIN_ROOM_SIZE = 45.0f;
    static constexpr float MAX_ROOM_SIZE = 65.0f;
    static constexpr float DIG_STEP_SIZE = 25.0f;
    static constexpr int DIRECTION_CHANGE_INCREMENT = 5;
    static constexpr int PLACE_ROOM_INCREMENT = 5;
    static constexpr int DUNGEON_ROOMS_LIMIT = 8;

    Point current_position;
    int change_direction_chance;
    int place_room_chance;
    DiggingDirection digging_direction;

public:
    explicit BlindAgentLevelGenerator(const BoundingBox& bounding_box)
     : Generator(bounding_box), current_position(0, 0) {};

    void run(Scene &scene) override;
private:
    void initialize_parameters(RandomNumberGenerator* random_generator);
    void dig();
    void place_corridor(Scene& scene, const Point& corridor_start);
    void place_room(Scene& scene, RandomNumberGenerator* random_generator);
};
