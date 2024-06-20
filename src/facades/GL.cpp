#include "GL.h"
#include "Window.h"

void GL::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int GL::Init() {
    glViewport(0, 0, Window::width, Window::height);
    glfwSetFramebufferSizeCallback(Window::window, GL::framebuffer_size_callback);  
    return 0;
}