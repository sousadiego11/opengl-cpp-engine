#include "Renderer.h"
#include "Window.h"
#include "Keyboard.h"
#include "TextureLoader.h"
#include <string.h>
#include <math.h>

void Renderer::Update() {
    while(!glfwWindowShouldClose(Window::window)) {
        Keyboard::ListenQuit();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwPollEvents();
        Renderer::Render();
        glfwSwapBuffers(Window::window);
    }

    glfwTerminate();
}

void Renderer::Render() {
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //BINDS THE MEMORY MANAGEMENT TO A EL ARRAY BUFFER
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //COPIES THE BUFFER DATA FROM VERTICES TO THE CORRESPONDING ARRAY BUFFER ON VBO
    
    // stride and indexes are length in bytes, so it has to be multiplied by the value of float
    // POSITION VECTOR: location, size, type, normalized, stride(length of the vtx array), index(where it starts)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // stride and indexes are length in bytes, so it has to be multiplied by the value of float
    // POSITION VECTOR: location, size, type, normalized, stride(length of the vtx array), index(where it starts)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // stride and indexes are length in bytes, so it has to be multiplied by the value of float
    // POSITION VECTOR: location, size, type, normalized, stride(length of the vtx array), index(where it starts)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);

    int vertexShader = Renderer::CompileShader("src/shaders/basic-vertex.glsl", GL_VERTEX_SHADER);
    int fragmentShader = Renderer::CompileShader("src/shaders/basic-fragment.glsl", GL_FRAGMENT_SHADER);
    int shaderProgram = Renderer::ShaderProgram(vertexShader, fragmentShader);
    // unsigned int textureId = TextureLoader::Load("src/textures/container.jpg");

    // DRAW
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int Renderer::ShaderProgram(int vtx, int frg) {
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

    glUseProgram(shaderProgram);
    glDeleteShader(vtx);
    glDeleteShader(frg);
    return shaderProgram;
}

int Renderer::CompileShader(const std::string& path, GLuint program) {
    const char* anyShaderSource = Renderer::ReadFromFile(path);
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
    char* shaderCode = new char[shaderCodeString.length() + 1];
    strcpy(shaderCode, shaderCodeString.c_str());

    return shaderCode;
}