#pragma once
#include <string>
#include <utility>

struct DescriptionComponent {
    int tag;
    std::string name;

    DescriptionComponent() = delete;

    DescriptionComponent(const DescriptionComponent& other) = default;

    explicit DescriptionComponent(int tag)
        : tag(tag) {}

    DescriptionComponent(int tag, std::string name)
        : tag(tag), name(std::move(name)) {}

};



