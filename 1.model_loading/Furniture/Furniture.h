//
// Created by saif on 1/15/25.
//

#ifndef LEARNOPENGL_FURNITURE_H
#define LEARNOPENGL_FURNITURE_H

#include <iostream>
#include "glad/glad.h"
#include "iostream"
#include "stb_image.h"
#include "learnopengl/shader_m.h"
#include "learnopengl/filesystem.h"
#include "learnopengl/camera.h"


using namespace std;

class Furniture {

    string TEXTUREBACK;
    GLuint textureBack;
    constexpr static const unsigned int indices[6] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    Shader shader;

public:
    Furniture() : shader(FileSystem::getPath("src/1.getting_started/7.4.camera_class/7.4.camera.vs").c_str(),
                         FileSystem::getPath("src/1.getting_started/7.4.camera_class/7.4.camera.fs").c_str()) {


    }


    void draw(unsigned int &VAO, unsigned int &texture, glm::mat4 modelBase, Camera camera) {


        shader.use();
        shader.setInt("texture", 0);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) 800 / (float) 600, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shader.use();

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setMat4("model", modelBase);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

private:
    void build(GLuint &VAO, GLuint &VAOBack, GLuint &VBO, GLuint &VBOBack, GLuint &EBO, GLuint &texture,
               GLfloat *array,
               GLsizeiptr size, const char *image, const char *imageBack, string place) {


        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, size, array, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);


        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char *data = stbi_load(
                image, &width,
                &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        if (place == "front") {
            array[2] -= 0.01f;
            array[10] -= 0.01f;
            array[18] -= 0.01f;
            array[26] -= 0.01f;
        } else if (place == "back") {
            array[2] += 0.01f;
            array[10] += 0.01f;
            array[18] += 0.01f;
            array[26] += 0.01f;
        } else if (place == "left") {
            array[0] += 0.01f;
            array[8] += 0.01f;
            array[16] += 0.01f;
            array[24] += 0.01f;
        } else if (place == "right") {
            array[0] -= 0.01f;
            array[8] -= 0.01f;
            array[16] -= 0.01f;
            array[24] -= 0.01f;
        } else if (place == "up") {
            array[1] -= 0.01f;
            array[9] -= 0.01f;
            array[17] -= 0.01f;
            array[25] -= 0.01f;
        } else if (place == "down") {
            array[1] += 0.01f;
            array[9] += 0.01f;
            array[17] += 0.01f;
            array[25] += 0.01f;
        }

        glGenVertexArrays(1, &VAOBack);
        glGenBuffers(1, &VBOBack);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAOBack);

        glBindBuffer(GL_ARRAY_BUFFER, VBOBack);

        glBufferData(GL_ARRAY_BUFFER, size, array, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);


        glGenTextures(1, &this->textureBack);
        glBindTexture(GL_TEXTURE_2D, this->textureBack);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int widthBack, heightBack, nrChannelsBack;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char *dataBack = stbi_load(
                imageBack, &widthBack,
                &heightBack, &nrChannelsBack, 0);
        if (dataBack) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthBack, heightBack, 0, GL_RGB, GL_UNSIGNED_BYTE, dataBack);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(dataBack);


    }


};


#endif //LEARNOPENGL_FURNITURE_H
