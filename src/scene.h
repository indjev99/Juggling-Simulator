#pragma once

#include "ball.h"
#include "color.h"
#include "vec2d.h"

#include <vector>

struct Scene
{
    Scene(const Vec2d size, const Color backColor):
        size(size),
        backColor(backColor),
        t(0) {}

    Vec2d size;
    Color backColor;

    double getTime() const;
    const std::vector<Ball>& getBalls() const;

    void step(double dt);

    void setG(const Vec2d& g);

    int addBall(double rad, const Color& col);

    void addThrowCatch(int id, double throwTime, const Vec2d& throwPos, double catchTime, const Vec2d& catchPos);

private:

    void addThrow(int id, double time, const Vec2d& pos, const Vec2d& vel);
    void addCatch(int id, double time, const Vec2d& pos);

    void bounceOff(Ball& ball, const Vec2d& acc);

    Vec2d g;

    double t;

    std::vector<Ball> balls;
};
