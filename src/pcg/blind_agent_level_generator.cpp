#include <iostream>
#include "src/pcg/blind_agent_level_generator.h"

void BlindAgentLevelGenerator::run(Scene &scene) {
    DLOG(INFO) << "BlindAgentLevelGenerator running";

    auto& random_generator = scene.get_random_generator();

    initialize_parameters(&random_generator);
    int placed_rooms = 0;
    Point corridor_start = current_position;

    while(placed_rooms < DUNGEON_ROOMS_LIMIT) {
        dig();
        int random = random_generator.random(100);
        if (random <= change_direction_chance) {
            if (placed_rooms > 0)
                place_corridor(scene, corridor_start);
            corridor_start = current_position;
            digging_direction = static_cast<DiggingDirection>(random_generator.random(4));
            change_direction_chance = 0;
        } else {
            change_direction_chance += 5;
        }

        random = random_generator.random(100);
        if (random <= place_room_chance) {
            place_room(scene, &random_generator);
            if (placed_rooms > 0)
                place_corridor(scene, corridor_start);
            corridor_start = current_position;
            ++placed_rooms;
            place_room_chance = 0;
        } else {
            place_room_chance += 5;
        }
    }


    DLOG(INFO) << "BlindAgentLevelGenerator finished";
}

void BlindAgentLevelGenerator::initialize_parameters(RandomNumberGenerator* random_generator) {
    current_position.x = random_generator->random(MIN_ROOM_SIZE / 2, bounding_box.get_width() - MIN_ROOM_SIZE / 2);
    current_position.y = random_generator->random(MIN_ROOM_SIZE / 2, bounding_box.get_height() - MIN_ROOM_SIZE / 2);
    change_direction_chance = 5;
    place_room_chance = 5;
    digging_direction = static_cast<DiggingDirection>(random_generator->random(4));

}

void BlindAgentLevelGenerator::dig() {
    switch(digging_direction) {
        case DiggingDirection::up:
            current_position.y = std::max(current_position.y - DIG_STEP_SIZE, MIN_ROOM_SIZE / 2);
            break;
        case DiggingDirection::right:
            current_position.x = std::min(current_position.x + DIG_STEP_SIZE, bounding_box.get_width() - MIN_ROOM_SIZE / 2 - 1);
            break;
        case DiggingDirection::down:
            current_position.y = std::min(current_position.y + DIG_STEP_SIZE, bounding_box.get_height() - MIN_ROOM_SIZE / 2 - 1);
            break;
        case DiggingDirection::left:
            current_position.x = std::max(current_position.x - DIG_STEP_SIZE, MIN_ROOM_SIZE / 2);         
    }
}

void BlindAgentLevelGenerator::place_room(Scene& scene, RandomNumberGenerator* random_generator) {
    int room_size = random_generator->random(MIN_ROOM_SIZE, MAX_ROOM_SIZE);

    // if room_size would exceed level boundingbox it will be equal to maximum placable room size
    room_size = std::min<float>(room_size, (bounding_box.get_width() - current_position.x) * 2);
    room_size = std::min<float>(room_size, (bounding_box.get_height() - current_position.y) * 2);

    room_size = std::min<float>(room_size, current_position.x * 2);
    room_size = std::min<float>(room_size, current_position.y * 2);

    auto room_bbox = BoundingBox(current_position.shifted_by(-room_size / 2, -room_size / 2), current_position.shifted_by(room_size / 2, room_size / 2));
    auto simple_room_generator = SimpleRoomGenerator(room_bbox);
    simple_room_generator.run(scene);
}

void BlindAgentLevelGenerator::place_corridor(Scene& scene, const Point& corridor_start) {
    auto corridor_first_bbox = BoundingBox(Point(corridor_start), Point(corridor_start));
    auto corridor_second_bbox = BoundingBox(Point(current_position), Point(current_position));

    auto corridor_generator = CorridorGenerator(corridor_first_bbox, corridor_second_bbox);
    corridor_generator.run(scene);
}
