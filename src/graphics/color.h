#pragma once
#include <SDL.h>

typedef SDL_Color Color;

namespace Colors{
    inline constexpr Color Black = {.r = 0, .g = 0, .b = 0, .a = 255};
    inline constexpr Color Red = {.r = 255, .g = 0, .b = 0, .a = 255};
    inline constexpr Color Green = {.r = 0, .g = 255, .b = 0, .a = 255};
    inline constexpr Color Blue = {.r = 0, .g = 0, .b = 255, .a = 255};
}
