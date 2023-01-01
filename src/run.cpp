#include "run.h"

#include "draw.h"
#include "scene.h"

void run(GLFWwindow* window)
{
    Scene scene(Vec2d(2, 3), Color(0.65, 0.65, 0.65));

    scene.balls.emplace_back(0.05, Color(1, 0, 0));
    scene.balls.emplace_back(0.05, Color(0, 1, 0));
    scene.balls.emplace_back(0.05, Color(0, 0, 1));

    scene.balls[0].pos = Vec2d(0.3, 1.2);
    scene.balls[1].pos = Vec2d(-0.05, 1.9);
    scene.balls[2].pos = Vec2d(-0.33, 1.1);

    while (!glfwWindowShouldClose(window))
    {
        drawScene(window, scene);
        glfwPollEvents();
    }
}
