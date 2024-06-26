#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <glad/glad.h>
#include <iostream>

class TextureLoader {
public:
    static unsigned int Load(const char* path, int unit);
};

#endif // TEXTURELOADER_H