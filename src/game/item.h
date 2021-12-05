#pragma once

#include <string>

class Item {
    std::string name;

public:

    explicit Item(std::string name) : name(std::move(name)) {}

    [[nodiscard]] const std::string& get_name() const{
        return name;
    }
};



