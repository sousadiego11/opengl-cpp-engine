#include "Keyboard.h"
#include "Window.h"

void Keyboard::ListenQuit() {
    if (Keyboard::GetKeyPressed(GLFW_KEY_ESCAPE)) {
        Window::Close();
    }
}

bool Keyboard::GetKeyPressed(int key) {
    return glfwGetKey(Window::window, key) == GLFW_PRESS;
}