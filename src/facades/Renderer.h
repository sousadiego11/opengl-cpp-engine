#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <memory>

#include <fstream>
#include <sstream>

class Renderer {
public:
    static void Update();
    static void BindGeometry();
    static void Render();
    static void PaintBackground();
};

#endif // RENDERER_H
