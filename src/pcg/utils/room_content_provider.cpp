#include <glog/logging.h>
#include "src/core/components/graphics_component.h"
#include "src/core/components/transformation_component.h"
#include "src/core/entity.h"
#include "src/pcg/utils/entity_creator.h"
#include "src/pcg/utils/room_content_provider.h"
#include <iostream>

RoomContentProviderImpl::RoomContentProviderImpl(bool is_used, bool generate_new, const std::string& data_filepath) {
    this->generate_new = generate_new;
    this->is_used = is_used;
    this->data_filepath = data_filepath;
}

void RoomContentProviderImpl::load_data_from_file(const std::string& filepath) {
    DLOG(INFO) << "Loading room content from file " + filepath;

    auto arr = cnpy::npy_load(filepath);

    int32_t* data_ptr = reinterpret_cast<int32_t*>(arr.data_holder->data());

    for(size_t i = 0; i < arr.shape[0]; ++i) {
        std::vector<std::vector<int32_t>> room(ROOM_SIZE, std::vector<int32_t>(ROOM_SIZE));

        int32_t* base_ptr = data_ptr + (arr.shape[0] - i - 1) * ROOM_SIZE * ROOM_SIZE;
        for(int j = 0; j < ROOM_SIZE; ++j) {
            memcpy(room[j].data(), base_ptr + j * ROOM_SIZE, sizeof(int32_t) * ROOM_SIZE);
        }

        rooms.push_back(room);
    }
}

Room RoomContentProviderImpl::get_next_room() {
    
    if(rooms.empty() && generate_new == true) {
        generate_rooms();
        load_data_from_file("generated_images.npy");
    } else if (rooms.empty() && generate_new == false) {
        load_data_from_file(data_filepath);
    }

    auto room = rooms[rooms.size() - 1];
    rooms.pop_back();

    return room;
}

void RoomContentProviderImpl::generate_rooms() const {
    system("python infer.py");
}

bool RoomContentProviderImpl::is_enabled() const {
    return is_used;
}
