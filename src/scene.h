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

    void step(double dt);

    Vec2d size;
    Color backColor;

    Vec2d g;

    std::vector<Ball> balls;

    double t;
};
