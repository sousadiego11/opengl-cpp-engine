#include "Window.h"
#include "Keyboard.h"

GLFWwindow* Window::window = nullptr;

int Window::MakeContext() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window::window = glfwCreateWindow(Window::width, Window::height, "OpenGLFirstProject", NULL, NULL);
    if (Window::window == NULL) {
        std::cout << "Error has occurred while trying to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(Window::window);
    return 0;
}

void Window::Close() {
    glfwSetWindowShouldClose(Window::window, true);
}