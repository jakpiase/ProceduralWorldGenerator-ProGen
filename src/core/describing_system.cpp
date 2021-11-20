#pragma once
#include <iostream>
#include <glog/logging.h>
#include "src/core/components/description_component.h"
#include "src/core/describing_system.h"

void DescribingSystem::update() {
    //DLOG(INFO) << "Describing system update running";

    auto view = registry.view<DescriptionComponent>();

    for (auto entity : view) {
        DescriptionComponent &descriptionComponent = view.get<DescriptionComponent>(entity);
        std::cout << descriptionComponent.description << std::endl;
    }
}
