#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

unsigned int TextureLoader::Load(const char* name) {
    unsigned int textureId;
    try {
        int width, height, nrChannels;
        unsigned char* textureData = stbi_load(name, &width, &height, &nrChannels, 0); 

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(textureData);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to load texture: " << e.what() << '\n';
    }
    return textureId;
}
