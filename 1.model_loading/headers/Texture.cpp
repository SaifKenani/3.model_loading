#include "Tex.h"
#include <iostream>

Tex::Tex(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
    type = texType;

    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    if (bytes) {
        if (numColCh == 1) {
            format = GL_RED;
        } else if (numColCh == 3) {
            format = GL_RGB;

        } else if (numColCh == 4) {
            format = GL_RGBA;

        } else {
            std::cerr << "Unsupported number of channels: " << numColCh << std::endl;
            stbi_image_free(bytes);
            return;
        }

        // إنشاء Texture في OpenGL
        glGenTextures(1, &ID);
        glActiveTexture(slot);
        glBindTexture(texType, ID);

        // إعداد خيارات التغليف والترشيح
        glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // تعيين الصورة كـ Texture
        glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
        glGenerateMipmap(texType);

        // تحرير البيانات المحملة
        stbi_image_free(bytes);

        // فك الربط مع Texture
        glBindTexture(texType, 0);
    } else {
        std::cerr << "Failed to load texture: " << image << std::endl;
    }
}

void Tex::texUnit(Shader &shader, const char *uniform, GLuint unit) {
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    shader.use();
    glUniform1i(texUni, unit);
}

void Tex::Bind() {
    glBindTexture(type, ID);
}

void Tex::Unbind() {
    glBindTexture(type, 0);
}

void Tex::Delete() {
    glDeleteTextures(1, &ID);
}

void Tex::setTexture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
    type = texType;

    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    if (bytes) {
        if (numColCh == 1) {
            format = GL_RED;
        } else if (numColCh == 3) {
            format = GL_RGB;

        } else if (numColCh == 4) {
            format = GL_RGBA;

        } else {
            std::cerr << "Unsupported number of channels: " << numColCh << std::endl;
            stbi_image_free(bytes);
            return;
        }

        // إنشاء Texture في OpenGL
        glGenTextures(1, &ID);
        glActiveTexture(slot);
        glBindTexture(texType, ID);

        // إعداد خيارات التغليف والترشيح
        glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // تعيين الصورة كـ Texture
        glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
        glGenerateMipmap(texType);

        // تحرير البيانات المحملة
        stbi_image_free(bytes);

        // فك الربط مع Texture
        glBindTexture(texType, 0);
    } else {
        std::cerr << "Failed to load texture: " << image << std::endl;
    }
}

