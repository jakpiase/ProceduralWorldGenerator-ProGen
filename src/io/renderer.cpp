#pragma once
#include <glog/logging.h>
#include "renderer.h"

Renderer::Renderer(Window& window) {
    handle = SDL_CreateRenderer(window.get_handle(), -1, SDL_RENDERER_ACCELERATED);
    if (handle == nullptr) {
        LOG(ERROR) << "Could not create renderer. Error: " << SDL_GetError();
    } else {
        LOG(INFO) << "Successfully created renderer";
    }
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(handle);
}

SDL_Renderer* Renderer::get_handle() {
    return handle;
}

void Renderer::render(Texture& texture, BoundingBox& box) {
    const SDL_Rect destination_rect = convert_to_sdl_rect(box);

    if (SDL_RenderCopy(handle, texture.get_handle(), nullptr, &destination_rect)) {
        LOG(ERROR) << "Could not render texture. Error: " << SDL_GetError();
    };
}

void Renderer::render(Color& color, BoundingBox& box) {
    set_drawing_color(color);
    const SDL_Rect destination_rect = convert_to_sdl_rect(box);

    if (SDL_RenderFillRect(handle, &destination_rect)) {
        LOG(ERROR) << "Could not render rectangle. Error: " << SDL_GetError();
    }
}

void Renderer::clear(const Color& color) {
    set_drawing_color(color);
    SDL_RenderClear(handle);
}

void Renderer::updateFrame() {
    SDL_RenderPresent(handle);
}

void Renderer::set_drawing_color(const Color& color) {
    if (SDL_SetRenderDrawColor(handle, color.r, color.g, color.b, color.a)) {
        LOG(ERROR) << "Could not set render draw color. Error: " << SDL_GetError();
    }
}

SDL_Rect Renderer::convert_to_sdl_rect(const BoundingBox& box) {
    const Point top_left = box.get_top_left();
    return {
            .x = static_cast<int>(top_left.x),
            .y = static_cast<int>(top_left.y),
            .w = static_cast<int>(box.get_width()),
            .h = static_cast<int>(box.get_height())
    };
}





