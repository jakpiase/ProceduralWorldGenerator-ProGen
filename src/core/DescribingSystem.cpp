#include <iostream>
#include "components/DescriptionComponent.h"
#include "DescribingSystem.h"

void DescribingSystem::update() {
    auto view = registry.view<DescriptionComponent>();

    for (auto entity : view) {
        DescriptionComponent &descriptionComponent = view.get<DescriptionComponent>(entity);
        std::cout << descriptionComponent.description << std::endl;
    }
}
