#include <glog/logging.h>
#include "src/core/components/graphics_component.h"
#include "src/core/components/transformation_component.h"
#include "src/core/entity.h"
#include "src/pcg/utils/entity_creator.h"
#include "src/pcg/utils/room_content_provider.h"
#include <entt/locator/locator.hpp>

void EntityCreatorImpl::create_corridor_floor(Scene& scene, const BoundingBox2i& corridor_box) const {
    DLOG(INFO) << "Creating corridor floor entity with box: " << corridor_box;

    Entity entity = scene.create_entity();
    entity.add_component<TransformationComponent>(corridor_box.get_top_left());
    entity.add_component<GraphicsComponent>(Colors::Darkslategrey, corridor_box.get_dimensions());

    DLOG(INFO) << "Created corridor floor";
}

void EntityCreatorImpl::create_room_floor(Scene& scene, const BoundingBox2i& room_box) const {
    DLOG(INFO) << "Creating room floor entity with box: " << room_box;

    handle_room_content_generation(scene, room_box);
    Entity entity = scene.create_entity();
    entity.add_component<TransformationComponent>(room_box.get_top_left());
    entity.add_component<GraphicsComponent>(Colors::Gainsboro, room_box.get_dimensions());

    DLOG(INFO) << "Created room floor";
}

Color get_color_for_room_tile(int32_t room_tile) {
    switch(room_tile) {
        case 0:
            return Colors::Gainsboro;
        case 1:
            return Colors::Red;
        case 2:
            return Colors::Gold;
        case 3:
            return Colors::RoyalBlue;
        case 4:
            return Colors::Brown;
        case 5:
            return Colors::SaddleBrown;
        case 6:
            return Colors::Dimgrey;
        default:
            throw new std::runtime_error("Unrecognized room tile type");
    }
}

void EntityCreatorImpl::handle_room_content_generation(Scene& scene, const BoundingBox2i& room_box) const {
    RoomContentProvider& RCP = entt::service_locator<RoomContentProvider>::ref();

    if(RCP.is_enabled() == false || room_box.get_height() != 7 || room_box.get_width() != 7){
        DLOG(INFO) << "Skipping generation of room content";
        return;
    }

    DLOG(INFO) << "Generating room content";

    auto room = RCP.get_next_room();

    for(size_t i = 0; i < room.size(); ++i) {
        for(size_t j = 0; j < room[0].size(); ++j) {
            Entity entity = scene.create_entity();
            entity.add_component<TransformationComponent>(room_box.get_top_left().shifted_by(i, j));
            entity.add_component<GraphicsComponent>(get_color_for_room_tile(room[i][j]), Dimensions2i(1, 1));
        }
    }
}
