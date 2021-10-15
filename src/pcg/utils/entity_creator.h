#pragma once

#include "src/core/scene.h"
#include "src/core/common/bounding_box.h"

class EntityCreator {
public:
    virtual void create_corridor_floor(Scene& scene, const BoundingBox2i& corridor_box) const = 0;

    virtual void create_room_floor(Scene& scene, const BoundingBox2i& room_box) const = 0;
};

class EntityCreatorImpl : public EntityCreator{
public:
    void create_corridor_floor(Scene& scene, const BoundingBox2i& corridor_box) const override;

    void create_room_floor(Scene& scene, const BoundingBox2i& room_box) const override;
};



