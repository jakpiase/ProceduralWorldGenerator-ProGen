#pragma once

#include "src/core/scene.h"
#include "src/core/common/bounding_box.h"
#include "deps/cnpy/cnpy.h"

class RoomContentProvider {
public:
    virtual void load_data_from_file(const std::string& filepath) = 0;

    virtual std::vector<std::vector<int32_t>> get_next_room() = 0;

    virtual void generate_rooms() const = 0;

    virtual bool is_enabled() const = 0;
protected:
    bool is_used;
    bool generate_new;
    std::vector<std::vector<std::vector<int32_t>>> rooms;
    std::string data_filepath;
    static constexpr int32_t ROOM_SIZE = 7;
};

class RoomContentProviderImpl : public RoomContentProvider{
public:
    RoomContentProviderImpl(bool is_used, bool generate_new, const std::string& data_filepath);

    void load_data_from_file(const std::string& filepath) override;

    std::vector<std::vector<int32_t>> get_next_room() override;

    void generate_rooms() const override;

    bool is_enabled() const override;
};



