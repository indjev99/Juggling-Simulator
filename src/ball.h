#pragma once

#include "color.h"
#include "move.h"
#include "vec2d.h"

#include <deque>

struct Ball
{
    Ball(double rad, const Color& col, const Vec2d& pos):
        rad(rad),
        col(col),
        pos(pos),
        inHand(false) {}

    double rad;
    Color col;

    Vec2d pos;
    Vec2d vel;

    bool inHand;
    std::deque<Move> moves;
};
