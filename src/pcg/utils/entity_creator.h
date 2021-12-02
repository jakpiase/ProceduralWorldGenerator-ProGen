#pragma once

#include "src/core/scene.h"
#include "src/core/common/bounding_box.h"
#include "room_content_provider.h"

class EntityCreator {
public:
    virtual void create_corridor_floor(Scene& scene, const BoundingBox2i& corridor_box) const = 0;

    virtual void create_room_floor(Scene& scene, const BoundingBox2i& room_box) const = 0;
};

class EntityCreatorImpl : public EntityCreator{
public:
    void create_corridor_floor(Scene& scene, const BoundingBox2i& corridor_box) const override;

    void create_room_floor(Scene& scene, const BoundingBox2i& room_box) const override;

    void handle_room_content_generation(Scene& scene, const BoundingBox2i& room_box) const;

    void parse_room_content_to_entities(Scene& scene, const Room& room, const BoundingBox2i& room_box) const;
};



