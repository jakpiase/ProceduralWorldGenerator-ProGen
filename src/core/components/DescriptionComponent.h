#pragma once

struct DescriptionComponent {
    std::string description;

    DescriptionComponent() = default;
    DescriptionComponent(const DescriptionComponent&) = default;

    explicit  DescriptionComponent(const std::string& description)
        : description(description) {}

};



