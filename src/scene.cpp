#include "scene.h"

#include "my_math.h"

#include <cassert>

double Scene::getTime() const
{
    return t;
}

const std::vector<Ball>& Scene::getBalls() const
{
    return balls;
}

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

#include <iostream>

void Scene::step(double dt)
{
    for (Ball& ball : balls)
    {
        Vec2d acc;
        Vec2d jrk;

        while (!ball.moves.empty() && ball.moves.front().t < t + EPS)
        {
            std::cout.precision(2);
            if (ball.moves.front().type == Move::Catch) std::cerr << "Catch " << ball.moves.front().t << " " << ball.moves.front().pos << std::endl;
            else std::cerr << "Throw " << ball.moves.front().t << " " << ball.moves.front().pos << " " << ball.moves.front().vel << std::endl;

            if (ball.moves.front().type == Move::Throw) ball.inHand = false;
            else if (ball.moves.front().type == Move::Catch) ball.inHand = true;
            ball.moves.pop_front();
        }

        if (!ball.inHand)
        {
            acc = g;
        }
        else if (ball.moves.empty())
        {
            acc = -50 * ball.vel;
        }
        else
        {
            const Move& nextThrow = ball.moves.front();
            double timeLeft = nextThrow.t - t;
            Vec2d avgVel = (nextThrow.pos - ball.pos) / timeLeft;
            Vec2d avgAcc = (nextThrow.vel - ball.vel) / timeLeft;
            acc = 6 * (avgVel - ball.vel) / timeLeft - 2 * avgAcc;
            jrk = 2 * (avgAcc - acc) / timeLeft;
        }

        ball.pos += ball.vel * dt + acc * dt * dt / 2 + jrk * dt * dt * dt / 6;
        ball.vel += acc * dt + jrk * dt * dt / 2;

        bounceOff(ball, acc);
    }

    t += dt;
}

void Scene::setG(const Vec2d& g)
{
    this->g = g;
}

int Scene::addBall(double rad, const Color& col)
{
    balls.emplace_back(rad, col);
    balls.back().pos = Vec2d(0, rad);
    balls.back().inHand = true;
    return balls.size() - 1;
}

void Scene::addThrowCatch(int id, double throwTime, const Vec2d& throwPos, double catchTime, const Vec2d& catchPos)
{
    assert(catchTime > throwTime);
    double flightTime = (catchTime - throwTime);
    Vec2d avgVel = (catchPos - throwPos) / flightTime;
    Vec2d throwVel = avgVel - g * flightTime / 2;
    addThrow(id, throwTime, throwPos, throwVel);
    addCatch(id, catchTime, catchPos);
}

void Scene::addThrow(int id, double time, const Vec2d& pos, const Vec2d& vel)
{
    Ball& ball = balls[id];
    if (ball.moves.empty()) assert(ball.inHand && time > t);
    else assert(ball.moves.back().type == Move::Catch && time > ball.moves.back().t);
    ball.moves.emplace_back(Move::Throw, time, pos, vel);
}

void Scene::addCatch(int id, double time, const Vec2d& pos)
{
    Ball& ball = balls[id];
    if (ball.moves.empty()) assert(!ball.inHand && time > t);
    else assert(ball.moves.back().type == Move::Throw && time > ball.moves.back().t);
    ball.moves.emplace_back(Move::Catch, time, pos);
}
