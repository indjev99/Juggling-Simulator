#pragma once

#include "vec2d.h"

#include <vector>

struct PatternElem
{
    int beats;
    double beatTime;
    double holdTime;
    Vec2d catchPos;
    Vec2d throwPos;
};

using Pattern = std::vector<PatternElem>;