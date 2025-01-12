//
// Created by saif on 1/12/25.
//

#ifndef LEARNOPENGL_POLYGON_H
#define LEARNOPENGL_POLYGON_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "learnopengl/shader_m.h"
#include "Tex.h"

class Polygon {
public:
    VAO *vao;
    VBO *vbo;
    EBO *ebo;
    Shader *shader;
    Tex *texture0;
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;
    Camera *camera;
    const char *image;
public:
    Polygon(GLfloat *vertices, GLsizeiptr size, const char *image) {
        this->image = image;
        GLuint indices[] =
                {
                        0, 2, 1, // Upper triangle
                        0, 3, 2 // Lower triangle
                };

        vao = new class VAO;
        vbo = new class VBO(vertices, size);
        vao->Bind();

        vao->LinkAttrib(*vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *) 0);
        vao->LinkAttrib(*vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *) (3 * sizeof(float)));
        vao->LinkAttrib(*vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *) (6 * sizeof(float)));

        ebo = new EBO(indices, sizeof(indices));

        vao->Unbind();
        vbo->Unbind();
        //  EBO9.Unbind();


        shader = new Shader(FileSystem::getPath("src/3.model_loading/1.model_loading/Polygon/polygon.vs").c_str(),
                            FileSystem::getPath("src/3.model_loading/1.model_loading/Polygon/polygon.fs").c_str());

        texture0 = new Tex(this->image, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
        texture0->texUnit(*shader, "texture0", 0);


    }

    Polygon() {}

    void Drow(Camera camera, glm::mat4 model) {
        this->camera = &camera;
        vao->Bind();
        shader->use();
        glm::mat4 projection = glm::perspective(glm::radians(this->camera->Zoom), (float) 800 / (float) 600, 0.1f,100.0f);
        glm::mat4 view = this->camera->GetViewMatrix();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        shader->setMat4("model", model);
        texture0->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void Delete() {
        vao->Delete();
        vbo->Delete();
        texture0->Delete();

    }


};


#endif //LEARNOPENGL_POLYGON_H
