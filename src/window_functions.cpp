#include "window_functions.h"

#include "window_size.h"

#include <glfw3.h>
#include <iostream>

const int START_WINDOW_SIZE = 720;

int windowWidth = START_WINDOW_SIZE;
int windowHeight = START_WINDOW_SIZE;

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

void windowSizeCallback(GLFWwindow* window, int width, int height)
{
    windowWidth = width;
    windowHeight = height;
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
    w = glfwCreateWindow(windowWidth, windowHeight, "Juggling Simulator", NULL, NULL);
    return w != nullptr;
}

bool setWindowCallbacks(GLFWwindow* w)
{
    glfwSetKeyCallback(w, keyCallback);
    glfwSetMouseButtonCallback(w, mouseButtonCallback);
    glfwSetCursorPosCallback(w, mousePositionCallback);
    glfwSetWindowSizeCallback(w, windowSizeCallback);
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
