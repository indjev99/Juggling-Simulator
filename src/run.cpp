#include "run.h"

#include "draw.h"
#include "scene.h"

#include <iostream>

const double STEPS_PER_SEC = 120;
const double INITIAL_FPS = 60;

const std::vector<Color> colors = {
    Color(1, 0, 0),
    Color(0, 1, 0),
    Color(0, 0, 1),
    Color(1, 1, 0),
    Color(1, 0, 1),
    Color(0, 1, 1)
};

Scene setupScene(int balls, double airTime, double holdTime, bool reverse = false, int throws = 10000)
{
    Scene scene(Vec2d(2, 3), Color(0.65, 0.65, 0.65));

    scene.setG(Vec2d(0, -9.8));

    double startTime = 0.5;
    double cycleTime = airTime + holdTime;
    double beatTime = cycleTime / balls;

    Vec2d rInPos(0.1, 1.2);
    Vec2d lInPos(-0.1, 1.2);
    Vec2d rOutPos(0.25, 1.2);
    Vec2d lOutPos(-0.25, 1.2);

    Vec2d rlInOutPos[2][2] = {
        {rInPos, rOutPos},
        {lInPos, lOutPos}
    };

    for (int i = 0; i < balls; ++i)
    {
        scene.addBall(0.05, colors[i % colors.size()]);     
    }

    for (int i = 0; i < throws; ++i)
    {
        int ball = i % balls;
        int throwHand = i % 2;
        int catchHand = (i + balls) % 2;
        int throwIO = 0 ^ reverse;
        int catchIO = 1 ^ reverse;
        const Vec2d& throwPos = rlInOutPos[throwHand][throwIO];
        const Vec2d& catchPos = rlInOutPos[catchHand][catchIO];
        double throwTime = startTime + i * beatTime + holdTime;
        double catchTime = startTime + i * beatTime + cycleTime;
        scene.addThrowCatch(ball, throwTime, throwPos, catchTime, catchPos);
    }

    return scene;
}

void run(GLFWwindow* window)
{
    int balls;
    bool reverse;
    double airTime;
    double holdTime;
    double slowmo;

    std::cin >> balls >> reverse >> airTime >> holdTime >> slowmo;

    Scene scene = setupScene(balls, airTime, holdTime, reverse);

    double dt = 1 / STEPS_PER_SEC;
    double fps = INITIAL_FPS;

    double start = glfwGetTime();
    double nextTime = 0;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        double time = glfwGetTime() - start;

        if (time >= nextTime)
        {
            drawScene(window, scene);
            nextTime += 1 / fps;
            while (scene.getTime() + dt / 2 < nextTime / slowmo)
            {
                scene.step(dt);
            }
            double frameTime = glfwGetTime() - start - time;
            while (fps > 1 && 1 / frameTime < fps) --fps;
            while (1 / frameTime > fps + 5) ++fps;
        }
    }
}
