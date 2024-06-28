#include "Renderer.h"
#include "Window.h"
#include "Keyboard.h"
#include "TextureLoader.h"
#include <string.h>
#include <math.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

unsigned int VAO, VBO, EBO, shaderProgram;

void Renderer::Update() {

    Renderer::BindRectangleContainer();

    int vertexShader = Renderer::CompileShader("src/shaders/basic-vertex.glsl", GL_VERTEX_SHADER);
    int fragmentShader = Renderer::CompileShader("src/shaders/basic-fragment.glsl", GL_FRAGMENT_SHADER);
    shaderProgram = Renderer::ShaderProgram(vertexShader, fragmentShader);

    unsigned int textureId1 = TextureLoader::Load("src/textures/container.jpg", GL_TEXTURE0);
    unsigned int textureId2 = TextureLoader::Load("src/textures/awesomeface.png", GL_TEXTURE1);

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

    while(!glfwWindowShouldClose(Window::window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Keyboard::ListenQuit();
        Renderer::Render();
        glfwPollEvents();
        glfwSwapBuffers(Window::window);
    }

    glfwTerminate();
}

void Renderer::BindRectangleContainer() {
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

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
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
}

void Renderer::Render() {
    unsigned int transformUnifLocation = glGetUniformLocation(shaderProgram, "transform");
    glm::mat4 transform;
    
    // DRAW ONE CONTAINER WITH THIS TRANSFORMATION BINDED TO THE SHADERS
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5, 0.0));
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));  
    glUniformMatrix4fv(transformUnifLocation, 1, GL_FALSE, glm::value_ptr(transform));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // NOW DRAW THE SECOND CONTAINER WITH THIS TRANSFORMATION BINDED TO THE SHADERS
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-0.5f, 0.5, 0.0));
    transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f) * sin((float)glfwGetTime()));
    glUniformMatrix4fv(transformUnifLocation, 1, GL_FALSE, &transform[0][0]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

unsigned int Renderer::ShaderProgram(int vtx, int frg) {
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

    return program;
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