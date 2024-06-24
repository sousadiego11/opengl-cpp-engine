#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <memory>

#include <fstream>
#include <sstream>

class Renderer {
public:
    static void Render();
    static void BoringTriangle();
    static int CompileShader(const std::string& path, GLuint program);
    static int LinkProgram(int vtx, int frg);
    static const char* ReadFromFile(const std::string& path);
};

#endif // RENDERER_H
