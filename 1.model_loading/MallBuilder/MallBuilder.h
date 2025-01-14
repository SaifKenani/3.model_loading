//
// Created by saif on 1/14/25.
//

#ifndef LEARNOPENGL_MALLBUILDER_H
#define LEARNOPENGL_MALLBUILDER_H

#include <algorithm>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Tex.h"
#include "learnopengl/filesystem.h"
#include "learnopengl/camera.h"
#include "iostream"

using namespace std;

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/dual_quaternion.hpp>

class MallBuilder {
public:

    //for Front
    GLuint VBORight, VAORight, VBORightBack, VAORightBack, EBO;
    GLuint VAOLeft, VBOLeft, VAOLeftBack, VBOLeftBack;
    GLuint VBOCenter, VAOCenter, VBOCenterBack, VAOCenterBack;
    GLuint VBODoor, VAODoor, VBODoorBack, VAODoorBack;
    GLuint VBOTop, VAOTop, VBOTopBack, VAOTopBack;
    GLuint textureRight, textureLeft, textureCenter, textureDoor, textureTop, textureBack;

    //fot 2 Wall right and left
    GLuint VAOWallRight, VAOWallRightBack, VBOWallRight, VBOWallRightBack, textureWallRight;
    GLuint VAOWallLeft, VAOWallLeftBack, VBOWallLeft, VBOWallLeftBack, textureWallLeft;
    // Back wall
    GLuint VAOBack, VAOBackBack, VBOBack, VBOBackBack, textureBackBack;

    // Up and Down Wall
    GLuint VAOUp, VAOUpBack, VBOUp, VBOUpBack, textureUp;
    GLuint VAODown, VAODownBack, VBODown, VBODownBack, textureDown;

    constexpr static const unsigned int indices[6] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    MallBuilder() {
        stbi_set_flip_vertically_on_load(true);

        GLfloat right[] = {
                // positions          // colors           // texture coords
                4.0f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                4.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                0.3f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                0.3f, 2.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat left[] = {
                // positions          // colors           // texture coords
                -0.3f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                -0.3f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -4.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -4.0f, 2.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat center[] = {
                // positions          // colors           // texture coords
                0.3f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                0.3f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -0.3f, 2.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat door[] = {
                // positions          // colors           // texture coords
                0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                0.3f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -0.3f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -0.3f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };

        GLfloat top[] = {
                // positions          // colors           // texture coords
                4.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                4.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -4.0f, 2.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -4.0f, 5.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat wallRight[] = {
                // positions          // colors           // texture coords
                4.0f, 5.0f, -6.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                4.0f, -1.0f, -6.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                4.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                4.0f, 5.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat wallLeft[] = {
                // positions          // colors           // texture coords
                -4.0f, 5.0f, -6.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                -4.0f, -1.0f, -6.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -4.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -4.0f, 5.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat back[] = {
                // positions          // colors           // texture coords
                4.0f, 5.0f, -6.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                4.0f, -1.0f, -6.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -4.0f, -1.0f, -6.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -4.0f, 5.0f, -6.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };

        GLfloat up[] = {
                // positions          // colors           // texture coords
                4.0f, 5.0f, -6.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                4.0f, 5.0f, -0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -4.0f, 5.0f, -0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -4.0f, 5.0f, -6.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };

        GLfloat down[] = {
                // positions          // colors           // texture coords
                4.0f, -1.0f, -6.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                4.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -4.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -4.0f, -1.0f, -6.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        build(VAORight, VAORightBack, VBORight, VBORightBack, EBO, textureRight, right, sizeof(right),
              FileSystem::getPath("src/3.model_loading/images/right.png").c_str(),
              FileSystem::getPath("resources/textures/block.png").c_str(), "front");

        build(VAOLeft, VAOLeftBack, VBOLeft, VBOLeftBack, EBO, textureLeft, left, sizeof(left),
              FileSystem::getPath("src/3.model_loading/images/right.png").c_str(),
              FileSystem::getPath("resources/textures/block.png").c_str(), "front");

        build(VAOCenter, VAOCenterBack, VBOCenter, VBOCenterBack, EBO, textureCenter, center, sizeof(center),
              FileSystem::getPath("src/3.model_loading/images/center.png").c_str(),
              FileSystem::getPath("resources/textures/block.png").c_str(), "front");

        build(VAODoor, VAODoorBack, VBODoor, VBODoorBack, EBO, textureDoor, door, sizeof(top),
              FileSystem::getPath("src/3.model_loading/images/photo_2024-12-04_10-51-1ddd5.jpg").c_str(),
              FileSystem::getPath("resources/textures/block.png").c_str(), "front");

        build(VAOTop, VAOTopBack, VBOTop, VBOTopBack, EBO, textureTop, top, sizeof(top),
              FileSystem::getPath("src/3.model_loading/images/photo_2024-12-04_10-51-1ddd5.jpg").c_str(),
              FileSystem::getPath("resources/textures/block.png").c_str(), "front");

        build(VAOWallRight, VAOWallRightBack, VBOWallRight, VBOWallRightBack, EBO, textureWallRight, wallRight,
              sizeof(wallRight),
              FileSystem::getPath("src/3.model_loading/images/photo_2024-12-04_10-51-1ddd5.jpg").c_str(),
              FileSystem::getPath("resources/textures/block.png").c_str(), "right");

        build(VAOWallLeft, VAOWallLeftBack, VBOWallLeft, VBOWallLeftBack, EBO, textureWallLeft, wallLeft,
              sizeof(wallLeft),
              FileSystem::getPath("src/3.model_loading/images/photo_2024-12-04_10-51-1ddd5.jpg").c_str(),
              FileSystem::getPath("resources/textures/block.png").c_str(), "left");

        build(VAOBack, VAOBackBack, VBOBack, VBOBackBack, EBO, textureBackBack, back,
              sizeof(wallLeft),
              FileSystem::getPath("src/3.model_loading/images/photo_2024-12-04_10-51-1ddd5.jpg").c_str(),
              FileSystem::getPath("resources/textures/block.png").c_str(), "back");

        build(VAOUp, VAOUpBack, VBOUp, VBOUpBack, EBO, textureUp, up,
              sizeof(wallLeft),
              FileSystem::getPath("src/3.model_loading/images/photo_2024-12-04_10-51-1ddd5.jpg").c_str(),
              FileSystem::getPath("resources/textures/block.png").c_str(), "up");


        build(VAODown, VAODownBack, VBODown, VBODownBack, EBO, textureDown, down,
              sizeof(wallLeft),
              FileSystem::getPath("src/3.model_loading/images/photo_2024-12-04_10-51-1ddd5.jpg").c_str(),
              FileSystem::getPath("resources/textures/block.png").c_str(), "down");


    }

    void DrowInterface(Camera camera, glm::mat4 modelBase) {


        this->drow(VAORight, textureRight, modelBase, camera);
        this->drow(VAORightBack, textureBack, modelBase, camera);

        this->drow(VAOLeft, textureLeft, modelBase, camera);
        this->drow(VAOLeftBack, textureBack, modelBase, camera);

        this->drow(VAOCenter, textureCenter, modelBase, camera);
        this->drow(VAOCenterBack, textureBack, modelBase, camera);

        this->drow(VAODoor, textureDoor, modelBase, camera);
        this->drow(VAODoorBack, textureBack, modelBase, camera);

        this->drow(VAOTop, textureTop, modelBase, camera);
        this->drow(VAOTopBack, textureBack, modelBase, camera);

        this->drow(VAOWallRight, textureWallRight, modelBase, camera);
        this->drow(VAOWallRightBack, textureBack, modelBase, camera);

        this->drow(VAOWallLeft, textureWallLeft, modelBase, camera);
        this->drow(VAOWallLeftBack, textureBack, modelBase, camera);

        this->drow(VAOBack, textureBackBack, modelBase, camera);
        this->drow(VAOBackBack, textureBack, modelBase, camera);

        this->drow(VAOUp, textureUp, modelBase, camera);
        this->drow(VAOUpBack, textureBack, modelBase, camera);


        this->drow(VAODown, textureDown, modelBase, camera);
        this->drow(VAODownBack, textureBack, modelBase, camera);

    }

    void draw2Wall() {

    }

    void
    build(GLuint &VAO, GLuint &VAOBack, GLuint &VBO, GLuint &VBOBack, GLuint &EBO, GLuint &texture,
          GLfloat *array,
          GLsizeiptr size, const char *image, const char *imageBack, string place) {


//        for (int i = 0; i <= 32; i++) {
//            if (i == 0 || i == 8 || i == 16 || i == 24 || i == 2 || i == 10 || i == 18 || i == 26 || i == 3 ||
//                i == 11 || i == 19 || i == 27 || i == 4 || i == 12 || i == 20 || i == 28) {
//                array[i] += 2;
//            }
//        }

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
        }else if (place == "up") {
            array[1] -= 0.01f;
            array[9] -= 0.01f;
            array[17] -= 0.01f;
            array[25] -= 0.01f;
        }else if (place == "down") {
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

    void drow(unsigned int &VAO, unsigned int &texture, glm::mat4 modelBase, Camera camera) {

        Shader ourShader(FileSystem::getPath("src/1.getting_started/7.4.camera_class/7.4.camera.vs").c_str(),
                         FileSystem::getPath("src/1.getting_started/7.4.camera_class/7.4.camera.fs").c_str());
        ourShader.use();
        ourShader.setInt("texture", 0);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) 800 / (float) 600, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.use();

        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        ourShader.setMat4("model", modelBase);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

};


#endif //LEARNOPENGL_MALLBUILDER_H
