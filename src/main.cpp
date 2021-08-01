#include <iostream>
#include <core/Scene.h>
#include "core/common/BoundingBox.h"
#include <pcg/SimpleLevelGenerator.h>

int main() {
    std::unique_ptr<Scene> mainScene = std::make_unique<Scene>();

    SimpleLevelGenerator levelGenerator(BoundingBox::fromZero(200.0, 200.0));
    levelGenerator.run(*mainScene);

    mainScene->update();

    return 0;
}
