#include "run.h"
#include "window_functions.h"

#include <iostream>

int main()
{
    GLFWwindow *window;
 
    if (setErrorCallback()) std::cerr << "GLFW error callback set" << std::endl;
    else return -1;
    
    if (initializeGLFW()) std::cerr << "GLFW initialized" << std::endl;
    else return -1;
    
    if (createWindow(window)) std::cerr << "Window created" << std::endl;
    else return -1;
    
    if (setWindowCallbacks(window)) std::cerr << "Window callbacks set" << std::endl;
    else return -1;

    run(window);

    if (destroyWindow(window)) std::cerr << "Window destroyed" << std::endl;
    else return -1;

    if (terminateGLFW()) std::cerr << "GLFW terminated" << std::endl;
    else return -1;

    return 0;
}
