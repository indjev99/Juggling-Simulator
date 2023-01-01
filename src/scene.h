#pragma once

#include "ball.h"
#include "color.h"
#include "vec2d.h"

#include <vector>

struct Scene
{
    Scene(const Vec2d size, const Color backColor):
        size(size),
        backColor(backColor) {}

    Vec2d size;
    Color backColor;

    std::vector<Ball> balls;
};
