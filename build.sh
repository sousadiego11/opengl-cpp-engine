#!/bin/bash

# Diretórios
INCLUDE_DIR=include
LIB_DIR=lib
SRC_DIR=src

# Arquivos fonte
SOURCES="
    $SRC_DIR/glad.c 
    $SRC_DIR/main.cpp 
    $SRC_DIR/facades/Window.cpp 
    $SRC_DIR/facades/GLAD.cpp 
    $SRC_DIR/facades/GLFW.cpp 
    $SRC_DIR/facades/GL.cpp 
    $SRC_DIR/facades/Keyboard.cpp
    $SRC_DIR/facades/Renderer.cpp
    $SRC_DIR/facades/TextureLoader.cpp
"

# Arquivo de saída
OUTPUT=opengl

# Bibliotecas
LIBS="-lglfw3dll -lopengl32 -lgdi32"

# Flags de compilação
CFLAGS="-I$INCLUDE_DIR"
LDFLAGS="-L$LIB_DIR"

# Compilação
g++ $CFLAGS $SOURCES $LDFLAGS $LIBS -o $OUTPUT

# Copiar a DLL para o diretório de saída (se necessário)
if [ ! -f "./glfw3.dll" ]; then
    cp $LIB_DIR/glfw3.dll ./
fi
