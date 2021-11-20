#pragma once
#include <array>

enum class Direction{
    Left,
    Top,
    Right,
    Bottom
};

constexpr std::array<Direction, 4> DIRECTIONS = {
        Direction::Left,
        Direction::Top,
        Direction::Right,
        Direction::Bottom
};
