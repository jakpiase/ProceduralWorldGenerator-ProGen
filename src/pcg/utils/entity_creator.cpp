#include <glog/logging.h>
#include "src/core/components/graphics_component.h"
#include "src/core/components/transformation_component.h"
#include "src/core/entity.h"
#include "src/pcg/utils/entity_creator.h"

void EntityCreatorImpl::create_corridor_floor(Scene& scene, const BoundingBox2i& corridor_box) const {
    DLOG(INFO) << "Creating corridor floor entity with box: " << corridor_box;

    Entity entity = scene.create_entity();
    entity.add_component<TransformationComponent>(corridor_box.get_top_left());
    entity.add_component<GraphicsComponent>(Colors::Blue, corridor_box.get_dimensions());

    DLOG(INFO) << "Created corridor floor";
}

void EntityCreatorImpl::create_room_floor(Scene& scene, const BoundingBox2i& room_box) const {
    DLOG(INFO) << "Creating room floor entity with box: " << room_box;

    Entity entity = scene.create_entity();
    entity.add_component<TransformationComponent>(room_box.get_top_left());
    entity.add_component<GraphicsComponent>(Colors::Red, room_box.get_dimensions());

    DLOG(INFO) << "Created room floor";
}

