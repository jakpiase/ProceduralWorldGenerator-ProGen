#pragma once
#include <SDL.h>
#include <string>

class Window {
private:
    SDL_Window* handle;

public:
    Window(const std::string& title, int width, int height);
    ~Window();

    [[nodiscard]] SDL_Window* get_handle();
};



