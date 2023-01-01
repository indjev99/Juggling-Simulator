#include "run.h"

#include "draw.h"
#include "scene.h"

void run(GLFWwindow* window)
{
    Scene scene;

    scene.size = Vec2d(20, 10);
    scene.backColor = Color(0.65, 0.65, 0.65);

    while (!glfwWindowShouldClose(window))
    {
        drawScene(window, scene);
        glfwPollEvents();
    }
}
