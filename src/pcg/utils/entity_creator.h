#pragma once
#include "src/core/scene.h"
#include "src/core/common/bounding_box.h"


class EntityCreator {
public:
    static void create_corridor_floor(Scene& scene, const BoundingBox2i& corridor_box);

    static void create_room_floor(Scene& scene, const BoundingBox2i& room_box);
};



