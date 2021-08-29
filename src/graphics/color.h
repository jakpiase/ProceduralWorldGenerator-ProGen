#pragma once
#include <SDL.h>

typedef SDL_Color Color;

namespace Colors{
    inline constexpr Color Black = {.a = 255};
    inline constexpr Color Red = {.r = 255, .a = 255};
    inline constexpr Color Green = {.g = 255, .a = 255};
    inline constexpr Color Blue = {.b = 255, .a = 255};

}
