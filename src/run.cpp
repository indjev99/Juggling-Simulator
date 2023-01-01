#include "run.h"

#include "draw.h"
#include "scene.h"

#include <iostream>

const double STEPS_PER_SEC = 1000;
const double INITIAL_FPS = 60;

void run(GLFWwindow* window)
{
    Scene scene(Vec2d(2, 3), Color(0.65, 0.65, 0.65));

    scene.g = Vec2d(0, -10);

    scene.balls.emplace_back(0.05, Color(1, 0, 0));
    scene.balls.emplace_back(0.05, Color(0, 1, 0));
    scene.balls.emplace_back(0.05, Color(0, 0, 1));

    scene.balls[0].pos = Vec2d(0.3, 1.2);
    scene.balls[0].vel = Vec2d(-0.3, 4.2);

    scene.balls[1].pos = Vec2d(-0.05, 1.9);
    scene.balls[1].vel = Vec2d(-1.2, 0.8);

    scene.balls[2].pos = Vec2d(-0.33, 1.1);
    scene.balls[2].vel = Vec2d(0.7, -4.4);

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
            while (scene.t + dt / 2 < nextTime)
            {
                scene.step(dt);
            }
            double frameTime = glfwGetTime() - start - time;
            while (fps > 1 && 1 / frameTime < fps) --fps;
            while (1 / frameTime > fps + 5) ++fps;
            std::cerr << fps << " : " << 1 / frameTime << std::endl;
        }
    }
}
