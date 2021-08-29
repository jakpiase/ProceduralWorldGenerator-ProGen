#pragma once
#include <SDL.h>
#include <glog/logging.h>
#include "src/graphics/texture.h"
#include "src/graphics/renderer.h"

Texture::Texture()
    : handle(nullptr) {}

Texture::Texture(Renderer &renderer, int width, int height) {
    handle = SDL_CreateTexture(renderer.get_handle(),
                               SDL_PIXELFORMAT_RGBA8888,
                               SDL_TEXTUREACCESS_STATIC,
                               width,
                               height);
    if (handle == nullptr) {
        LOG(ERROR) << "Could not create texture. Error: " << SDL_GetError();
    }
}

Texture::~Texture() {
    if(handle != nullptr){
        SDL_DestroyTexture(handle);
    }
}

bool Texture::isEmpty() const {
    return handle == nullptr;
}

SDL_Texture* Texture::get_handle() {
    return handle;
}
