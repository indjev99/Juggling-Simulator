#include "window_functions.h"

#include <iostream>

const int START_WIDTH = 480;
const int START_HEIGHT = 720;

void errorCallback(int error, const char* description)
{
    std::cerr << error << ": " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
}

void mousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
}

bool setErrorCallback()
{
    glfwSetErrorCallback(errorCallback);
    return true;
}

bool initializeGLFW()
{
    return glfwInit();
}

bool createWindow(GLFWwindow*& w)
{
    w = glfwCreateWindow(START_WIDTH, START_HEIGHT, "Juggling Simulator", NULL, NULL);
    return w != nullptr;
}

bool setWindowCallbacks(GLFWwindow* w)
{
    glfwSetKeyCallback(w, keyCallback);
    glfwSetMouseButtonCallback(w, mouseButtonCallback);
    glfwSetCursorPosCallback(w, mousePositionCallback);
    return true;
}

bool destroyWindow(GLFWwindow*& w)
{
    glfwDestroyWindow(w);
    w = nullptr;
    return true;
}

bool terminateGLFW()
{
    glfwTerminate();
    return true;
}
