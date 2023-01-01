#include "run.h"

#include "draw.h"
#include "scene.h"

#include <iostream>

const double STEPS_PER_SEC = 120;
const double INITIAL_FPS = 60;
const double SLOWMO = 1;

void run(GLFWwindow* window)
{
    Scene scene(Vec2d(2, 3), Color(0.65, 0.65, 0.65));

    scene.setG(Vec2d(0, -10));

    int redBall = scene.addBall(0.05, Color(1, 0, 0));

    for (int i = 0; i < 10; ++i)
    {
        scene.addThrow(redBall, 1 + i * 1.5, Vec2d(0.4, 1.5), Vec2d(-0.8, 5));
        scene.addCatch(redBall, 2 + i * 1.5);
    }

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
            while (scene.getTime() + dt / 2 < nextTime / SLOWMO)
            {
                scene.step(dt);
            }
            double frameTime = glfwGetTime() - start - time;
            while (fps > 1 && 1 / frameTime < fps) --fps;
            while (1 / frameTime > fps + 5) ++fps;
        }
    }
}
