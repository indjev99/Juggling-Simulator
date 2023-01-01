#include "scene.h"

void Scene::step(double dt)
{
    for (Ball& ball : balls)
    {
        ball.vel += g * dt;
        ball.pos += ball.vel * dt;

        if (ball.pos.y < ball.rad)
        {
            ball.pos.y = ball.rad;
            ball.vel.y = -ball.vel.y;
        }

        double maxX = size.x / 2 - ball.rad;

        if (ball.pos.x < -maxX)
        {
            ball.pos.x = -maxX;
            ball.vel.x = -ball.vel.x;
        }

        if (ball.pos.x > maxX)
        {
            ball.pos.x = maxX;
            ball.vel.x = -ball.vel.x;
        }
    }

    t += dt;
}
