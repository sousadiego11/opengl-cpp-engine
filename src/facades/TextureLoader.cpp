#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

unsigned int TextureLoader::Load(const char* path, const char* uniform, int unit, int shaderProgram, int location) {
    unsigned int textureId;
    try {
        int width, height, nrChannels;
        unsigned char* textureData = stbi_load(path, &width, &height, &nrChannels, 0);

        stbi_set_flip_vertically_on_load(true);

        glGenTextures(1, &textureId);
        glActiveTexture(unit);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(textureData);

        glUseProgram(shaderProgram);
        glUniform1i(glGetUniformLocation(shaderProgram, uniform), location);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to load texture: " << e.what() << '\n';
    }
    return textureId;
}
