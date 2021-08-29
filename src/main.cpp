#pragma once

#include <iostream>
#include <glog/logging.h>
#include <SDL.h>
#include "src/game.h"
#include "src/core/scene.h"
#include "src/core/common/bounding_box.h"
#include "src/pcg/binary_space_partitioning_level_generator.h"

#undef main //SDL defines main and it needs to be undefined


int main(int argc, const char* argv[]) {
    FLAGS_logtostderr = true;

    google::InitGoogleLogging(argv[0]);

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        LOG(ERROR) << "Could not initialize SDL! Error: " << SDL_GetError();
    }

    int exit_code = Game().run();

    SDL_Quit();
    google::ShutdownGoogleLogging();

    return exit_code;
}
