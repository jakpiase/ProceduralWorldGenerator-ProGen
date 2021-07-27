//
// Created by Maciej on 28.07.2021.
//

#include "Service.h"

void Service::add_entity(Entity& entity) {
    entities.push_back(&entity);
}
