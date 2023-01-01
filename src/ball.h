#pragma once

#include "color.h"
#include "vec2d.h"

struct Ball
{
    Ball(double rad, const Color& col):
        rad(rad),
        col(col) {}

    double rad;
    Color col;

    Vec2d pos;
    Vec2d speed;
};
