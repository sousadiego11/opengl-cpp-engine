#include "Renderer.h"
#include "Window.h"
#include "Keyboard.h"
#include <string.h>

void Renderer::Render() {
    while(!glfwWindowShouldClose(Window::window)) {
        Keyboard::ListenQuit();
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        Renderer::BoringTriangle();
        
        glfwSwapBuffers(Window::window);
    }

    glfwTerminate();
}

void Renderer::BoringTriangle() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //BINDS THE MEMORY MANAGEMENT TO A ARRAY BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //COPIES THE BUFFER DATA FROM VERTICES TO THE CORRESPONDING ARRAY BUFFER ON VBO
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    int vertexShader = Renderer::CompileShader("src/shaders/basic-vertex.glsl", GL_VERTEX_SHADER);
    int fragmentShader = Renderer::CompileShader("src/shaders/basic-fragment.glsl", GL_FRAGMENT_SHADER);
    int shaderProgram = Renderer::LinkProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // DRAW
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int Renderer::LinkProgram(int vtx, int frg) {
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vtx);
    glAttachShader(shaderProgram, frg);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    return shaderProgram;
}

int Renderer::CompileShader(const std::string& path, GLuint program) {
    const char* anyShaderSource = Renderer::ReadFromFile(path);
    unsigned int anyShader;
    anyShader = glCreateShader(program);
    glShaderSource(anyShader, 1, &anyShaderSource, NULL);
    glCompileShader(anyShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(anyShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(anyShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return anyShader;
}

const char* Renderer::ReadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "An error ocurred while trying to access the file: " << path << std::endl;
        return nullptr;
    }

    std::stringstream shaderStream;
    shaderStream << file.rdbuf();
    file.close();

    std::string shaderCodeString = shaderStream.str();
    char* shaderCode = new char[shaderCodeString.length() + 1]; // +1 for null terminator
    strcpy(shaderCode, shaderCodeString.c_str());

    return shaderCode;
}