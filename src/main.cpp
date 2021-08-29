#include <iostream>
#include <glog/logging.h>
#include "src/core/scene.h"
#include "src/core/common/bounding_box.h"
#include "src/pcg/binary_space_partitioning_level_generator.h"

int main(int argc, const char* argv[]) {
    FLAGS_logtostderr = true;

    google::InitGoogleLogging(argv[0]);
    LOG(INFO) << "Starting ProGen";

    std::unique_ptr<Scene> main_scene = std::make_unique<Scene>();
    BinarySpacePartitioningLevelGenerator level_generator(BoundingBox::from_zero(200.0, 200.0));
    level_generator.run(*main_scene);
    main_scene->update();

    LOG(INFO) << "ProGen exited succesfully";
    google::ShutdownGoogleLogging();

    return 0;
}
