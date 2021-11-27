#pragma once
#include <SDL.h>

typedef SDL_Color Color;

namespace Colors{
    inline constexpr Color Black = {.r = 0, .g = 0, .b = 0, .a = 255};
    inline constexpr Color Red = {.r = 255, .g = 0, .b = 0, .a = 255};
    inline constexpr Color Green = {.r = 0, .g = 255, .b = 0, .a = 255};
    inline constexpr Color Blue = {.r = 0, .g = 0, .b = 255, .a = 255};
    inline constexpr Color Gold = {.r = 255, .g = 215, .b = 0, .a = 255};
    inline constexpr Color Purple = {.r = 128, .g = 0, .b = 128, .a = 255};
    inline constexpr Color RoyalBlue = {.r = 65, .g = 105, .b = 225, .a = 255};
    inline constexpr Color Brown = {.r = 165, .g = 42, .b = 42, .a = 255};
    inline constexpr Color SaddleBrown = {.r = 139, .g = 69, .b = 19, .a = 255};
    inline constexpr Color DarkGrey = {.r = 169, .g = 169, .b = 169, .a = 255};
}
