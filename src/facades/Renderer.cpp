#include "Renderer.h"
#include "Window.h"
#include "Keyboard.h"

void Renderer::Render() {
    while(!glfwWindowShouldClose(Window::window)) {
        glfwSwapBuffers(Window::window);
        glfwPollEvents();
        Keyboard::ListenQuit();
    }

    glfwTerminate();
}