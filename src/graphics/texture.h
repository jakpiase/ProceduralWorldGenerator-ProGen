#pragma once
#include <SDL.h>

class Renderer;

class Texture {
private:
    SDL_Texture* handle;

public:
    Texture();
    Texture(Renderer& renderer, int width, int height);
    Texture(const Texture&) = delete;
    ~Texture();

    Texture& operator=(const Texture&) = delete;

    SDL_Texture* get_handle();

    bool isEmpty() const;
};



