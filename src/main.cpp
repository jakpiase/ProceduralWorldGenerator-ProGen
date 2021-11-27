#pragma once

#include <iostream>
#include <glog/logging.h>
#include <SDL.h>
//#include <cnpy.h>
#include <exception>
#include "src/game.h"

#undef main //SDL defines main and it needs to be undefined

void init_data() {
    system("python.exe infer.py");

    std::cout << "finished";
}

int main(int argc, const char* argv[]) {
    FLAGS_logtostderr = true;

    google::InitGoogleLogging(argv[0]);

    //init_data();
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        LOG(ERROR) << "Could not initialize SDL! Error: " << SDL_GetError();
    }

    int exit_code;

    try{
        exit_code = Game().run();
    } catch(std::exception& e){
        LOG(ERROR) << e.what();
        exit_code = -1;
    }

    SDL_Quit();
    google::ShutdownGoogleLogging();

    return exit_code;
}
