#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "facades/Window.h"
#include "facades/GLFW.h"
#include "facades/GLAD.h"
#include "facades/GL.h"

int main() {
    GLFW::Init();
    Window::Create(); // Calls after GLFW init
    GLAD::Init(); // Called after glfw context is set
    GL::Init(); // GL funcs called after GLAD is inited

    return 0;
}