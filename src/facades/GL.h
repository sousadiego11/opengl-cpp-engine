#ifndef GL_H
#define GL_H

#include <GLFW/glfw3.h>
#include <iostream>

class GL {
public:
    static int Init();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif // GL_H
