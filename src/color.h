#pragma once

struct Color
{
    Color(const Color& other) = default;

    Color(double r, double g, double b):
        r(r),
        g(g),
        b(b) {}

    Color():
        Color(0, 0, 0) {}

    double r, g, b;
};
