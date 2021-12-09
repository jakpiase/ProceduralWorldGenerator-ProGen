#pragma once
#include <string>
#include <vector>
#include "src/game/item.h"

struct ItemBagComponent {
    std::vector<Item> items;

    ItemBagComponent() = default;
};



