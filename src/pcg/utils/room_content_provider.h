#pragma once

#include "src/core/scene.h"
#include "src/core/common/bounding_box.h"
#include "src/cnpy/cnpy.h"

class RoomContentProvider {
public:
    virtual void load_data_from_file(const std::string& filepath) = 0;

    virtual std::vector<std::vector<int32_t>> get_next_room() = 0;

    virtual void generate_rooms() const = 0;

    virtual bool is_used() const = 0;

    virtual void set_is_used(bool is_used) = 0;

    virtual void set_generate_new_rooms(bool generate_new_room) = 0;

protected:
    bool used;
    bool generate_new_rooms;
    std::vector<std::vector<std::vector<int32_t>>> rooms;
    static constexpr int32_t ROOM_SIZE = 7;
};

class RoomContentProviderImpl : public RoomContentProvider{
public:
    void load_data_from_file(const std::string& filepath) override;

    std::vector<std::vector<int32_t>> get_next_room() override;

    void generate_rooms() const override;

    bool is_used() const override;

    void set_is_used(bool is_used) override;

    void set_generate_new_rooms(bool generate_new_room) override;
};



