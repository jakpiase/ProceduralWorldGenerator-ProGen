#include <vector>
#include "Entity.h"

class Service {

private:
    std::vector<Entity*> entities;

public:
    virtual void run() = 0;

    void add_entity(Entity& entity);
};

