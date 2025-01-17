//
// Created by saif on 1/16/25.
//

#ifndef LEARNOPENGL_FLOOR2_H
#define LEARNOPENGL_FLOOR2_H

#include "glad/glad.h"
#include <algorithm>
#include "learnopengl/filesystem.h"
#include "learnopengl/camera.h"
#include "iostream"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include "learnopengl/shader_m.h"

using namespace std;

class Floor2 {
    const unsigned int SCR_WIDTH = 1920;
    const unsigned int SCR_HEIGHT = 1080;


    GLuint VAOSeparator1, textureSeparator1;
    GLuint VAOSeparator2, textureSeparator2;



public:
    constexpr static const unsigned int indices[6] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    Shader ourShader;

    Floor2() : ourShader(FileSystem::getPath("src/1.getting_started/7.4.camera_class/7.4.camera.vs").c_str(),
                         FileSystem::getPath("src/1.getting_started/7.4.camera_class/7.4.camera.fs").c_str()) {
        setSeparator();
    }

    void drawWithTransparency(Camera camera,glm::mat4 baseModel){
        // Tow Separator
        glm::mat4 model=baseModel;
        this->draw(camera,model,VAOSeparator1,textureSeparator1);
        model = glm::translate(model, glm::vec3(+60.0, 0.0, 0.0));
        this->draw(camera,model,VAOSeparator1,textureSeparator1);

         model=baseModel;
        this->draw(camera,model,VAOSeparator2,textureSeparator2);
        model = glm::translate(model, glm::vec3(+20.0, 0.0, 0.0));
        this->draw(camera,model,VAOSeparator2,textureSeparator2);

        



    }
private:

    void setSeparator() {

        GLfloat separator1[] = {
                // positions          // colors           // texture coords
                -15.0f, 10.0f, -12.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                -15.0f, 5.0f, -12.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -3.0f, 5.0f, -12.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -3.0f, 10.0f, -12.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };
        setVAO(VAOSeparator1, separator1, sizeof(separator1));
        setTexture(textureSeparator1,FileSystem::getPath("src/3.model_loading/images/blur2.png").c_str());

        GLfloat separator2[] = {
                // positions          // colors           // texture coords
                -3.0f, 10.0f, -8.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                -3.0f, 5.0f, -8.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -3.0f, 5.0f, -0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -3.0f, 10.0f, -0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };
        setVAO(VAOSeparator2, separator2, sizeof(separator2));
        setTexture(textureSeparator2,FileSystem::getPath("src/3.model_loading/images/blur2.png").c_str());


    }

    void draw(Camera camera, glm::mat4 baseModel, GLuint VAO, GLuint texture) {


        ourShader.use();
        ourShader.setInt("texture", 0);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                                100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.use();

        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        ourShader.setMat4("model", baseModel);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }


    void setVAO(GLuint &VAO, GLfloat *array, GLsizeiptr size) {
        GLuint VBO, EBO;
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
    }

    void setVAOWithBack(GLuint &VAO, GLuint &VAOBack, GLfloat *array, GLsizeiptr size, string place) {
        GLuint VBO, EBO, VBOBack, EBOBack;
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

    }

    void setTexture(GLuint &texture, const char *image) {

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
    }

};


#endif //LEARNOPENGL_FLOOR2_H
