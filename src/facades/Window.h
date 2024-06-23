#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

class Window {
public:
    static const int width = 800;
    static const int height = 600;
    static GLFWwindow* window;

    static int MakeContext();
    static void Close();
};