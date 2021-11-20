
#include <iostream>
#include <glog/logging.h>
#include "src/core/components/physics_component.h"
#include "src/core/physics_system.h"

void PhysicsSystem::update() {
    //DLOG(INFO) << "Physics system update running";

    auto view = registry.view<PhysicsComponent>();

    for (auto entity : view) {
        //PhysicsComponent& physics_component = view.get<PhysicsComponent>(entity);
        //std::cout << physics_component.bounding_box << std::endl;
    }
}
