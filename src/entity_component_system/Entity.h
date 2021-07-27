#pragma once

#include <vector>
#include "Component.h"

class Entity {

private:
    std::vector<Component> components;

public:
    Entity(std::vector<Component>& components);

    template<typename T>
    T* get_component();

};


