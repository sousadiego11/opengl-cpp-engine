#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GLFW/glfw3.h>
#include <iostream>

class Keyboard {
public:
    static void ListenQuit();
    static bool GetKeyPressed(int key);
};

#endif // KEYBOARD_H
