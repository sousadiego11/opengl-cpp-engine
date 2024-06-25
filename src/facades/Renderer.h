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
    static void MakeUniform(int programId);

    static int CompileShader(const std::string& path, GLuint program);
    static int ShaderProgram(int vtx, int frg);
    
    static const char* ReadFromFile(const std::string& path);
};

#endif // RENDERER_H
