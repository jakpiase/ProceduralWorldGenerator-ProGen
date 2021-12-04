#include <glog/logging.h>
#include <entt/locator/locator.hpp>
#include "src/pcg/utils/registry_utils.h"
#include "src/core/components/graphics_component.h"
#include "src/core/components/transformation_component.h"
#include "src/core/entity.h"
#include "src/pcg/utils/entity_creator.h"
#include "src/pcg/room_content/room_content_type.h"
#include "src/core/components/description_component.h"

Color get_color_for_room_tile(int32_t room_tile);

DescriptionComponent create_description_component(int32_t room_tile);

void EntityCreatorImpl::create_corridor_floor(Scene& scene, const BoundingBox2i& corridor_box) const {
    DLOG(INFO) << "Creating corridor floor entity with box: " << corridor_box;

    Entity entity = scene.create_entity();
    entity.add_component<TransformationComponent>(corridor_box.get_top_left());
    entity.add_component<GraphicsComponent>(Colors::Darkslategrey, corridor_box.get_dimensions());

    DLOG(INFO) << "Created corridor floor";
}

void EntityCreatorImpl::create_room_floor(Scene& scene, const BoundingBox2i& room_box) const {
    DLOG(INFO) << "Creating room floor entity with box: " << room_box;

    Entity entity = scene.create_entity();
    handle_room_content_generation(scene, room_box, entity.get_handle());
    entity.add_component<TransformationComponent>(room_box.get_top_left());
    entity.add_component<GraphicsComponent>(Colors::Gainsboro, room_box.get_dimensions());
    entity.add_component<DescriptionComponent>(RoomContentType::FLOOR);
    entt::service_locator<RegistryUtils>::ref().register_entity(scene.get_registry(), entity.get_handle());


    DLOG(INFO) << "Created room floor";
}


const int ROOM_SIZE = 7;

void EntityCreatorImpl::handle_room_content_generation(Scene& scene, const BoundingBox2i& room_box,
                                                       entt::entity room_entity) const {
    RoomContentProvider& room_content_provider = entt::service_locator<RoomContentProvider>::ref();

    if (room_content_provider.is_enabled() == false) {
        DLOG(INFO) << "Skipping generation of room content";
        return;
    }

    assert(room_box.get_height() == ROOM_SIZE && room_box.get_width() == ROOM_SIZE);
    DLOG(INFO) << "Generating room content";
    auto room = room_content_provider.get_next_room();
    parse_room_content_to_entities(scene, room, room_box, room_entity);
}

void
EntityCreatorImpl::parse_room_content_to_entities(Scene& scene, const Room& room, const BoundingBox2i& room_box,
                                                  entt::entity room_entity) {
    std::shared_ptr<RegistryUtils> registry_utils = entt::service_locator<RegistryUtils>::get().lock();

    bool is_processed[ROOM_SIZE][ROOM_SIZE];
    std::memset(is_processed, false, ROOM_SIZE * ROOM_SIZE);

    for (size_t i = 0; i < ROOM_SIZE; ++i) {
        for (size_t j = 0; j < ROOM_SIZE; ++j) {
            if (room[i][j] != RoomContentType::EMPTY && is_processed[i][j] == false) {
                Entity entity = scene.create_entity();
                entity.add_component<TransformationComponent>(room_box.get_top_left().shifted_by(j, i));
                entity.add_component<DescriptionComponent>(create_description_component(room[i][j]));

                switch (room[i][j]) {
                    case RoomContentType::TABLE: {
                        Dimensions2i room_dimensions = j + 2 < ROOM_SIZE && room[i][j + 2] == RoomContentType::TABLE ?
                                                       Dimensions2i(3, 2) : Dimensions2i(2, 3);
                        entity.add_component<GraphicsComponent>(get_color_for_room_tile(room[i][j]), room_dimensions);

                        for (size_t i1 = i; i1 < i + room_dimensions.height; ++i1) {
                            for (size_t j1 = j; j1 < j + room_dimensions.width; ++j1) {
                                is_processed[i1][j1] = true;
                            }
                        }
                        DLOG(INFO) << "Creating table from " << room_box.get_top_left().shifted_by(j, i)
                                   << " with dimensions " << room_dimensions;
                        break;
                    }
                    case RoomContentType::MONUMENT: {
                        const int MONUMENT_SIZE = 2;
                        entity.add_component<GraphicsComponent>(get_color_for_room_tile(room[i][j]),
                                                                Dimensions2i(2, 2));

                        for (size_t i1 = i; i1 < i + MONUMENT_SIZE; ++i1) {
                            for (size_t j1 = j; j1 < j + MONUMENT_SIZE; ++j1) {
                                is_processed[i1][j1] = true;
                            }
                        }
                        DLOG(INFO) << "Creating monument from " << room_box.get_top_left().shifted_by(j, i);
                        break;
                    }
                    case RoomContentType::DRAWER: {
                        Dimensions2i drawer_dimensions =
                                j + 1 < ROOM_SIZE && room[i][j + 1] == RoomContentType::DRAWER ?
                                Dimensions2i(2, 1) : Dimensions2i(1, 2);

                        entity.add_component<GraphicsComponent>(get_color_for_room_tile(room[i][j]), drawer_dimensions);

                        for (size_t i1 = i; i1 < i + drawer_dimensions.height; ++i1) {
                            for (size_t j1 = j; j1 < j + drawer_dimensions.width; ++j1) {
                                is_processed[i1][j1] = true;
                            }
                        }
                        DLOG(INFO) << "Creating drawer from " << room_box.get_top_left().shifted_by(j, i)
                                   << " with dimensions " << drawer_dimensions;
                        break;
                    }

                    default:
                        entity.add_component<GraphicsComponent>(get_color_for_room_tile(room[i][j]),
                                                                Dimensions2i(1, 1));
                        break;
                }

                registry_utils->register_entity(scene.get_registry(), entity.get_handle(), room_entity);
                is_processed[i][j] = true;
            }
        }
    }
}

Color get_color_for_room_tile(int32_t room_tile) {
    switch (room_tile) {
        case RoomContentType::ENEMY:
            return Colors::Red;
        case RoomContentType::TREASURE:
            return Colors::Gold;
        case RoomContentType::WATER:
            return Colors::RoyalBlue;
        case RoomContentType::TABLE:
            return Colors::Brown;
        case RoomContentType::DRAWER:
            return Colors::SaddleBrown;
        case RoomContentType::MONUMENT:
            return Colors::Dimgrey;
        default:
            throw std::runtime_error("Unrecognized room tile type");
    }
}


std::string create_name(int32_t room_tile) {
    static int name_index = 0;
    std::string index = std::to_string(name_index++);
    switch (room_tile) {
        case RoomContentType::ENEMY:
            return "Enemy" + index;
        default:
            return "";
    }
}

DescriptionComponent create_description_component(int32_t room_tile) {

    return DescriptionComponent(room_tile, create_name(room_tile));
}
