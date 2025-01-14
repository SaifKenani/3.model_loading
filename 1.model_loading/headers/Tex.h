#ifndef TEX_CLASS_H
#define TEX_CLASS_H

#include<glad/glad.h>
#include<stb_image.h>

#include"learnopengl/shader_m.h"

class Tex {
public:
    GLuint ID;
    GLenum type;

    Tex(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);


    // Assigns a texture unit to a texture
    void texUnit(Shader &shader, const char *uniform, GLuint unit);

    // Binds a texture
    void Bind();

    // Unbinds a texture
    void Unbind();

    // Deletes a texture
    void Delete();

    void setTexture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
};

#endif