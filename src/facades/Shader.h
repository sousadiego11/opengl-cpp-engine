#pragma once
#include <glad/glad.h>
#include <iostream>

class Shader {
public:
    static int Compile(const std::string& path, GLuint program);
    static unsigned int Program(int vtx, int frg);
};