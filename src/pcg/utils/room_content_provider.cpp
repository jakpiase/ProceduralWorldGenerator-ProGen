#include <glog/logging.h>
#include "src/core/components/graphics_component.h"
#include "src/core/components/transformation_component.h"
#include "src/core/entity.h"
#include "src/pcg/utils/entity_creator.h"
#include "src/pcg/utils/room_content_provider.h"
#include <iostream>

void RoomContentProviderImpl::load_data_from_file(const std::string& filepath) {
    DLOG(INFO) << "Loading room contet data from file " + filepath;

    auto arr = cnpy::npy_load(filepath);

    int32_t* data_ptr = reinterpret_cast<int32_t*>(arr.data_holder->data());

    for(size_t i = 0; i < arr.shape[0]; ++i) {
        std::vector<std::vector<int32_t>> room(ROOM_SIZE, std::vector<int32_t>(ROOM_SIZE));

        int32_t* base_ptr = data_ptr + (arr.shape[0] - i - 1)*49;
        for(int j = 0; j < ROOM_SIZE; ++j) {
            memcpy(room[j].data(), base_ptr + j * ROOM_SIZE, sizeof(int32_t) * ROOM_SIZE);
        }

        rooms.push_back(room);
    }
}

std::vector<std::vector<int32_t>> RoomContentProviderImpl::get_next_room() {
    
    if(rooms.empty() && generate_new_rooms == true) {
        generate_rooms();
        load_data_from_file("valid_images.npy");
    } else if (rooms.empty() && generate_new_rooms == false) {
        load_data_from_file("valid_images.npy");
    }

    auto room = rooms[rooms.size() - 1];
    rooms.pop_back();

    std::cout << "rooms size" << rooms.size() << std::endl;

    return room;
}

void RoomContentProviderImpl::generate_rooms() const {
    system("python.exe infer.py");
}

bool RoomContentProviderImpl::is_used() const {
    return used;
}

void RoomContentProviderImpl::set_is_used(bool is_used) {
    used = is_used;
}

void RoomContentProviderImpl::set_generate_new_rooms(bool generate_new_rooms) {
    this->generate_new_rooms = generate_new_rooms;
}