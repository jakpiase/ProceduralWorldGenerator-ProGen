#include <iostream>
#include "core/Scene.h"
#include "core/common/BoundingBox.h"
#include "pcg/SimpleLevelGenerator.h"
#include <glog/logging.h>

int main(int argc, const char* argv[]) {
    FLAGS_logtostderr = true;
    google::InitGoogleLogging(argv[0]);
    LOG(INFO) << "Starting ProGen";

    std::unique_ptr<Scene> mainScene = std::make_unique<Scene>();
    SimpleLevelGenerator levelGenerator(BoundingBox::from_zero(200.0, 200.0));
    levelGenerator.run(*mainScene);
    mainScene->update();

    LOG(INFO) << "ProGen exited succesfully";
    google::ShutdownGoogleLogging();

    return 0;
}
