#include <iostream>
#include <glog/logging.h>
#include <SDL.h>
//#include <cnpy.h>
#include <exception>
#include <regex>
#include "src/game.h"

#undef main //SDL defines main and it needs to be undefined

static const std::string DEFAULT_ROOM_CONTENT_PATH = "valid_images.npy";

std::shared_ptr<RoomContentProvider> create_room_content_provider(int argc, const char* argv[]) {
    std::string room_content = "none";
    std::string room_content_path = DEFAULT_ROOM_CONTENT_PATH;

    std::regex room_content_regex("room_content=(none)|(static)|(generate)");
    std::regex room_content_path_regex("room_content_path=.*.npy");

    for(int i = 1; i < argc; ++i) {
        if(std::regex_search(argv[i], room_content_regex)) {
            if(std::regex_search(argv[i], std::regex("static"))) {
                room_content = "static";
            } else if(std::regex_search(argv[i], std::regex("generate"))) {
                room_content = "generate";
            }
        } else if (std::regex_search(argv[i], room_content_path_regex)) {
            room_content_path = argv[i];
        } else {
            LOG(WARNING) << "Unrecognized commandline argument: \"" << argv[i] << "\"!";
        }
    }

    LOG(INFO) << "Room content setting: " << room_content;
    LOG(INFO) << "Room content path: " << room_content_path;

    return std::make_shared<RoomContentProviderImpl>(room_content != "none", room_content == "generate", room_content_path);
}

int main(int argc, const char* argv[]) {
    FLAGS_logtostderr = true;

    google::InitGoogleLogging(argv[0]);

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        LOG(ERROR) << "Could not initialize SDL! Error: " << SDL_GetError();
    }

    auto room_content_provider = create_room_content_provider(argc, argv);

    int exit_code;

    try{
        exit_code = Game(room_content_provider).run();
    } catch(std::exception& e){
        LOG(ERROR) << e.what();
        exit_code = -1;
    }

    SDL_Quit();
    google::ShutdownGoogleLogging();

    return exit_code;
}
