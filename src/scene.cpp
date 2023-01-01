#include "scene.h"

#include "my_math.h"

void Scene::bounceOff(Ball& ball, const Vec2d& acc)
{
    Vec2d oldPotential = -ball.pos.pointwise(acc);

    double minY = ball.rad;
    double maxX = size.x / 2 - ball.rad;

    bool change = false;

    if (ball.pos.y < minY)
    {
        ball.pos.y = 2 * minY - ball.pos.y;
        ball.vel.y = -ball.vel.y;
        change = true;
    }

    if (ball.pos.x < -maxX)
    {
        ball.pos.x = 2 * -maxX - ball.pos.x;
        ball.vel.x = -ball.vel.x;
        change = true;
    }

    if (ball.pos.x > maxX)
    {
        ball.pos.x = 2 * maxX - ball.pos.x;
        ball.vel.x = -ball.vel.x;
        change = true;
    }

    if (change)
    {
        Vec2d newVelSign = ball.vel.applied(sign);
        Vec2d newVelSq = ball.vel.pointwise(ball.vel) + 2 * (oldPotential + ball.pos.pointwise(acc));
        ball.vel = newVelSq.applied([](double x){ return x >= 0 ? sqrt(x) : 0; }).pointwise(newVelSign);
    }
}

void Scene::step(double dt)
{
    for (Ball& ball : balls)
    {
        Vec2d acc = g;

        ball.pos += ball.vel * dt + acc * dt * dt / 2;
        ball.vel += acc * dt;

        bounceOff(ball, acc);
    }

    t += dt;
}
