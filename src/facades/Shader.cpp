#include "Shader.h"
#include "FileSystem.h"

unsigned int Shader::Program(int vtx, int frg) {
    unsigned int program = glCreateProgram();
    glAttachShader(program, vtx);
    glAttachShader(program, frg);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vtx);
    glDeleteShader(frg);
    glUseProgram(program);

    return program;
}

int Shader::Compile(const std::string& path, GLuint program) {
    const char* anyShaderSource = FileSystem::ReadFromFile(path);
    unsigned int anyShader;
    anyShader = glCreateShader(program);
    glShaderSource(anyShader, 1, &anyShaderSource, NULL);
    glCompileShader(anyShader);

    delete[] anyShaderSource;
    int  success;
    char infoLog[512];
    glGetShaderiv(anyShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(anyShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return anyShader;
}