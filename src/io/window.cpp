#pragma once
#include <glog/logging.h>
#include "src/io/window.h"

Window::Window(const std::string &title, int width, int height) {
    handle = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_UNDEFINED,           // initial x position
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_WINDOW_SHOWN);
    if (handle == nullptr) {
        LOG(ERROR) << "Could not create window with title: " << title << "Error: " << SDL_GetError();
    } else {
        LOG(INFO) << "Created window with title: " << title;
    }
}

Window::~Window() {
    SDL_DestroyWindow(handle);
}

SDL_Window* Window::get_handle() {
    return handle;
}
