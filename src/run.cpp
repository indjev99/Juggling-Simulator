#include "run.h"

#include "draw.h"
#include "scene.h"

void run(GLFWwindow* window)
{
    Scene scene;

    scene.radius = Vec2d(5, 5);
    scene.backColor = Color(0.65, 0.65, 0.65);

    while (!glfwWindowShouldClose(window))
    {
        drawScene(window, scene);
        glfwPollEvents();
    }
}
