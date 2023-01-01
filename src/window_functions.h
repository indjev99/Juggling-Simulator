#pragma once

#include <string>
#include <glfw3.h>

bool setErrorCallback();
bool initializeGLFW();
bool createWindow(GLFWwindow*& w);
bool setWindowCallbacks(GLFWwindow* w);
bool destroyWindow(GLFWwindow*& w);
bool terminateGLFW();
