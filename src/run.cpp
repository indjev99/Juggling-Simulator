#include "run.h"

#include "draw.h"

void run(GLFWwindow* window)
{
    while (!glfwWindowShouldClose(window))
    {
        drawScene(window);
        glfwPollEvents();
    }
}
