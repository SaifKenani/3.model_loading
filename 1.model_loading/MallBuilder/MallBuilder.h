//
// Created by saif on 1/14/25.
//

#ifndef LEARNOPENGL_MALLBUILDER_H
#define LEARNOPENGL_MALLBUILDER_H

#include <algorithm>
#include "learnopengl/filesystem.h"
#include "learnopengl/camera.h"
#include "learnopengl/shader_m.h"
#include "stb_image.h"

#include "iostream"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/dual_quaternion.hpp>

class MallBuilder {
    const unsigned int SCR_WIDTH = 1920;
    const unsigned int SCR_HEIGHT = 1080;

    string TEXTUREBACK;

    //for Front
    GLuint VBORight, VAORight, VBORightBack, VAORightBack, EBO;
    GLuint VAOLeft, VBOLeft, VAOLeftBack, VBOLeftBack;
    GLuint VBOCenter, VAOCenter, VBOCenterBack, VAOCenterBack;
    GLuint VBODoorRight, VAODoorRight, VBODoorRightBack, VAODoorRightBack;
    GLuint VBODoorLeft, VAODoorLeft, VBODoorLeftBack, VAODoorLeftBack;

    GLuint VBOTop, VAOTop, VBOTopBack, VAOTopBack;
    GLuint textureRight, textureLeft, textureCenter, textureDoorRight, textureDoorLeft, textureTop, textureBack;

    //fot 2 Wall right and left
    GLuint VAOWallRight, VAOWallRightBack, VBOWallRight, VBOWallRightBack, textureWallRight;
    GLuint VAOWallLeft, VAOWallLeftBack, VBOWallLeft, VBOWallLeftBack, textureWallLeft;
    // Back wall
    GLuint VAOBack, VAOBackBack, VBOBack, VBOBackBack, textureBackBack;

    // Up and Down Wall
    GLuint VAOUp, VAOUpBack, VBOUp, VBOUpBack, textureUp;
    GLuint VAODown, VAODownBack, VBODown, VBODownBack, textureDown;

    // Street
    GLuint VAOStreet, VBOStreet, textureStreet;
    GLuint VAOGrass, VBOGrass, textureGrass;
    // Cutter
    GLuint VAOCutter1Right, VBOCutter1Right, textureCutter1Right;

    //floor
    GLuint VAOFloor1, VBOFloor1, textureFloor1, VAOFloor1Complete, VBOFloor1Complete, textureFloor1Complete;

    GLuint VAOFloor2, VBOFloor2, textureFloor2, VAOFloor2Complete, VBOFloor2Complete, textureFloor2Complete;


    // Restaurant
    GLuint VAOBannerRestaurant, VAOBannerRestaurantBack, VBOBannerRestaurant, VBOBannerRestaurantBack, textureBannerRestaurant, textureBannerRestaurantBack;
    GLuint VAOBannerRestaurantSide, VAOBannerRestaurantBackSide, VBOBannerRestaurantSide, VBOBannerRestaurantBackSide, textureBannerRestaurantSide, textureBannerRestaurantBackSide;
    GLuint VAOShawarma, VBOShawarma, EBOShawarma, textureShawarma;

    //Restaurent and clothes
    GLuint VAOInterfaceRestaurant, VAOInterfaceRestaurantBack, VBOInterfaceRestaurant, VBOInterfaceRestaurantBack, textureInterfaceRestaurant, textureInterfaceRestaurantBack;
    GLuint VAOInterfaceCompleteRestaurant, VAOInterfaceCompleteRestaurantBack, VBOInterfaceCompleteRestaurant, VBOInterfaceCompleteRestaurantBack, textureInterfaceCompleteRestaurant, textureInterfaceCompleteRestaurantBack;
    GLuint VAOTable, VAOTableBack, VBOTable, textureTable, textureTableBack;
    GLuint VAOVertical, VAOVerticalBack, VBOTVertical, VBOTVerticalBack, textureTVertical, textureShawarmaInterface, textureShawarmaInterfaceComplete;


    // Clothes
    GLuint VAOBannerClothes, VBOBannerClothes, textureBannerClothes, VAOBannerClothesBack, VBOBannerClothesBack, textureBannerClothesBack;
    GLuint VAOBannerClothesSide, VBOBannerClothesSide, textureBannerClothesSide, VAOBannerClothesBackSide, VBOBannerClothesBackSide, textureBannerClothesBackSide;


    // Blouse
    GLuint VAOBlouseBody, VAOBlouseBodyBack, VBOBlouseBody, VBOBlouseBodyBack, textureBlouseBody, textureBlouseBodyBack;
    GLuint VAOBlouseLeft, VAOBlouseLeftBack, VBOBlouseLeft, VBOBlouseLeftBack, textureBlouseLeft, textureBlouseLeftBack;
    GLuint VAOBlouseLeftComplete, VAOBlouseLeftBackComplete, VBOBlouseLeftComplete, VBOBlouseLeftBackComplete, textureBlouseLeftComplete, textureBlouseLeftBackComplete;
    GLuint VAOBlouseRight, VAOBlouseRightBack, VBOBlouseRight, VBOBlouseRightBack, textureBlouseRight, textureBlouseRightBack;
    GLuint VAOBlouseRightComplete, VAOBlouseRightBackComplete, VBOBlouseRightComplete, VBOBlouseRightBackComplete, textureBlouseRightComplete, textureBlouseRightBackComplete;
    GLuint VAOBlouseCollar, VAOBlouseCollarBack, VBOBlouseCollar, VBOBlouseCollarBack, textureBlouseCollar, textureBlouseCollarBack;

    //Pants
    GLuint VAOPantsBody, VBOPantsBody, texturePantsBody;
    GLuint VAOPantsLeft, VBOPantsLeft, texturePantsLeft;
    GLuint VAOPantsRight, VBOPantsRight, texturePantsRight;
    GLuint VAOPantsBelt, VBOPantsBelt, texturePantsBelt;
    // setStaircase
    GLuint VAOStaircase, VBOStaircase, EBOStaircase, textureStaircase;
    GLuint VAOStaircaseSide, VBOStaircaseSide, EBOStaircaseSide, textureStaircaseSide;
    GLuint VAOUnderStaircase, VBOUnderStaircase, textureUnderStaircase;
    GLuint VAOUnderStaircaseComplete, VBOUnderStaircaseComplete, textureUnderStaircaseComplete;




    constexpr static const unsigned int indices[6] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
public:
    Shader ourShader;

    MallBuilder() : ourShader(FileSystem::getPath("src/1.getting_started/7.4.camera_class/7.4.camera.vs").c_str(),
                              FileSystem::getPath("src/1.getting_started/7.4.camera_class/7.4.camera.fs").c_str()) {
        TEXTUREBACK = "src/3.model_loading/images/wood.png";
        setVAO();
        setCutterAndFloor();
        banner();
        setShawarma();
        setTableForChef();
        buildTexture(textureShawarmaInterface,
                     FileSystem::getPath("src/3.model_loading/images/shawarmainterface.png").c_str());
        buildTexture(textureShawarmaInterfaceComplete,
                     FileSystem::getPath("src/3.model_loading/images/shawarmaleft.png").c_str());
        buildTexture(textureStaircase, FileSystem::getPath("src/3.model_loading/images/back.jpeg").c_str());
        setBlouse();
        setPants();

        setStaircase();
    }


    void build(GLuint &VAO, GLuint &VAOBack, GLuint &VBO, GLuint &VBOBack, GLuint &EBO, GLuint &texture,
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

    void buildTexture(GLuint &texture, const char *image) {

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

    void draw(GLuint VAO, GLuint texture, glm::mat4 modelBase, Camera camera) {


        ourShader.use();
        ourShader.setInt("texture", 0);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                                100.0f);
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


    void DrowInterface(Camera camera, glm::mat4 modelBase) {

        //street and grass
        drawStreet(camera, modelBase);

        //right of mall
        this->draw(VAORight, textureRight, modelBase, camera);
        this->draw(VAORightBack, textureBack, modelBase, camera);

        //left of mall
        this->draw(VAOLeft, textureLeft, modelBase, camera);
        this->draw(VAOLeftBack, textureBack, modelBase, camera);

        //up door of mall
        this->draw(VAOCenter, textureCenter, modelBase, camera);
        this->draw(VAOCenterBack, textureBack, modelBase, camera);

//        this->draw(VAOTop, textureTop, modelBase, camera);
//        this->draw(VAOTopBack, textureBack, modelBase, camera);

        // wall right
        this->draw(VAOWallRight, textureWallRight, modelBase, camera);
        this->draw(VAOWallRightBack, textureBack, modelBase, camera);

        // wall left
        this->draw(VAOWallLeft, textureWallLeft, modelBase, camera);
        this->draw(VAOWallLeftBack, textureBack, modelBase, camera);

        // wall behind
        this->draw(VAOBack, textureBackBack, modelBase, camera);
        this->draw(VAOBackBack, textureBack, modelBase, camera);

        // wall up
        this->draw(VAOUp, textureUp, modelBase, camera);
        this->draw(VAOUpBack, textureBack, modelBase, camera);

        // wall down
        this->draw(VAODown, textureDown, modelBase, camera);
        this->draw(VAODownBack, textureBack, modelBase, camera);

        // floor divider
        this->draw(VAOFloor1, textureFloor1, modelBase, camera);
        this->draw(VAOFloor1Complete, textureFloor1Complete, modelBase, camera);
        this->draw(VAOFloor2, textureFloor2, modelBase, camera);
        this->draw(VAOFloor2Complete, textureFloor2Complete, modelBase, camera);



        // banner of restaurant
        this->draw(VAOBannerRestaurant, textureBannerRestaurant, modelBase, camera);
        this->draw(VAOBannerRestaurantBack, textureBack, modelBase, camera);

        // banner of clothes
        this->draw(VAOBannerClothes, textureBannerClothes, modelBase, camera);
        this->draw(VAOBannerClothesBack, textureBack, modelBase, camera);

        // restaurant banner side
        this->draw(VAOBannerRestaurantSide, textureBannerRestaurantSide, modelBase, camera);
        this->draw(VAOBannerRestaurantBackSide, textureBack, modelBase, camera);

        // clothes banner side
        this->draw(VAOBannerClothesSide, textureBannerClothesSide, modelBase, camera);
        this->draw(VAOBannerClothesBackSide, textureBack, modelBase, camera);

        // back of shawarma
        glm::mat4 model = modelBase;
        model = glm::translate(model, glm::vec3(-40.0, 0.0, -15.0));
        this->draw(VAOVertical, textureTVertical, model, camera);
        model = modelBase;
        model = glm::translate(model, glm::vec3(-40.0, 0.0, -15.0));
        this->draw(VAOVerticalBack, textureBack, model, camera);

        // center of shawarma
        model = modelBase;
        model = glm::translate(model, glm::vec3(-42.0, 0.0, -10.8));
        model = glm::scale(model, glm::vec3(0.1f, 1.0, 1.0));
        this->draw(VAOVertical, textureTVertical, model, camera);


        //grill or restaurant up
        model = modelBase;
        model = glm::translate(model, glm::vec3(0.0, -0.0, +3.5));
        this->draw(VAOTable, textureTable, model, camera);
        //grill or restaurant down
        model = modelBase;
        model = glm::translate(model, glm::vec3(0.0, +10.0, +3.5));
        this->draw(VAOTable, textureTable, model, camera);


        // interface restaurant
        model = modelBase;
        this->draw(VAOInterfaceRestaurant, textureShawarmaInterface, model, camera);
        // complete interface restaurant
        model = modelBase;
        this->draw(VAOInterfaceCompleteRestaurant, textureShawarmaInterfaceComplete, model, camera);

//        this->draw(VAODownBack, textureBack, modelBase, camera);

        // draw blouse and pants
        model = modelBase;
        model = glm::translate(model, glm::vec3(15.0, 10.0, -1.0));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        this->drawBlouse(camera, model, textureBlouseBody, textureBlouseRight, textureBlouseLeft, textureBlouseCollar);

        model = modelBase;
        model = glm::translate(model, glm::vec3(15.0, 8.3, -1.0));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        this->drawPants(camera, model, texturePantsLeft, texturePantsRight, texturePantsBelt);


        // draw blouse and pants
        {
            // draw blouse and pants
            model = modelBase;
            model = glm::translate(model, glm::vec3(15.0, 10.0, -1.0));
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
            this->drawBlouse(camera, model, textureBlouseBody, textureBlouseRight, textureBlouseLeft,
                             textureBlouseCollar);

            model = modelBase;
            model = glm::translate(model, glm::vec3(15.0, 8.3, -1.0));
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            this->drawPants(camera, model, texturePantsLeft, texturePantsRight, texturePantsBelt);


            // draw blouse and pants
            model = modelBase;
            model = glm::translate(model, glm::vec3(22.0, 10.0, -1.0));
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
            this->drawBlouse(camera, model, textureBlouseBody, textureBlouseRight, textureBlouseLeft,
                             textureBlouseCollar);

            model = modelBase;
            model = glm::translate(model, glm::vec3(22.0, 8.3, -1.0));
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            this->drawPants(camera, model, texturePantsLeft, texturePantsRight, texturePantsBelt);


            // draw blouse and pants
            model = modelBase;
            model = glm::translate(model, glm::vec3(29.0, 10.0, -1.0));
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
            this->drawBlouse(camera, model, textureBlouseBody, textureBlouseRight, textureBlouseLeft,
                             textureBlouseCollar);

            model = modelBase;
            model = glm::translate(model, glm::vec3(29.0, 8.3, -1.0));
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            this->drawPants(camera, model, texturePantsLeft, texturePantsRight, texturePantsBelt);

            // draw blouse and pants
            model = modelBase;
            model = glm::translate(model, glm::vec3(36.0, 10.0, -1.0));
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
            this->drawBlouse(camera, model, textureBlouseBody, textureBlouseRight, textureBlouseLeft,
                             textureBlouseCollar);

            model = modelBase;
            model = glm::translate(model, glm::vec3(36.0, 8.3, -1.0));
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            this->drawPants(camera, model, texturePantsLeft, texturePantsRight, texturePantsBelt);


            model = modelBase;
            model = glm::translate(model, glm::vec3(43.0, 10.0, -1.0));
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
            this->drawBlouse(camera, model, textureBlouseBody, textureBlouseRight, textureBlouseLeft,
                             textureBlouseCollar);

            model = modelBase;
            model = glm::translate(model, glm::vec3(43.0, 8.3, -1.0));
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            this->drawPants(camera, model, texturePantsLeft, texturePantsRight, texturePantsBelt);
        }


        // draw list of blouse
        {
            model = modelBase;
            model = glm::translate(model, glm::vec3(47.8, -0.2, -5.5));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
            this->drawBlouse(camera, model, textureBlouseBody, textureBlouseRight, textureBlouseLeft,
                             textureBlouseCollar);

            model = modelBase;
            model = glm::translate(model, glm::vec3(47.8, -0.2, -9.5));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
            this->drawBlouse(camera, model, textureBlouseBody, textureBlouseRight, textureBlouseLeft,
                             textureBlouseCollar);

            model = modelBase;
            model = glm::translate(model, glm::vec3(47.8, -0.2, -13.5));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
            this->drawBlouse(camera, model, textureBlouseBody, textureBlouseRight, textureBlouseLeft,
                             textureBlouseCollar);

            model = modelBase;
            model = glm::translate(model, glm::vec3(47.8, -0.2, -17.5));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
            this->drawBlouse(camera, model, textureBlouseBody, textureBlouseRight, textureBlouseLeft,
                             textureBlouseCollar);

            model = modelBase;
            model = glm::translate(model, glm::vec3(47.8, -0.2, -21.5));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
            this->drawBlouse(camera, model, textureBlouseBody, textureBlouseRight, textureBlouseLeft,
                             textureBlouseCollar);
        }

        //draw list of pants
        {
            model = modelBase;
            model = glm::translate(model, glm::vec3(13.5, -0.2, -1.0));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.6, 0.6, 0.6));
            this->drawPants(camera, model, texturePantsLeft, texturePantsRight,
                            texturePantsBelt);

            model = modelBase;
            model = glm::translate(model, glm::vec3(13.5, -0.2, -6.0));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.6, 0.6, 0.6));
            this->drawPants(camera, model, texturePantsLeft, texturePantsRight,
                            texturePantsBelt);

            model = modelBase;
            model = glm::translate(model, glm::vec3(13.5, -0.2, -11.0));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.6, 0.6, 0.6));
            this->drawPants(camera, model, texturePantsLeft, texturePantsRight,
                            texturePantsBelt);

            model = modelBase;
            model = glm::translate(model, glm::vec3(13.5, -0.2, -16.0));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.6, 0.6, 0.6));
            this->drawPants(camera, model, texturePantsLeft, texturePantsRight,
                            texturePantsBelt);

            model = modelBase;
            model = glm::translate(model, glm::vec3(13.5, -0.2, -21.0));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.6, 0.6, 0.6));
            this->drawPants(camera, model, texturePantsLeft, texturePantsRight,
                            texturePantsBelt);

        }


        // Staircase and slide
        {

            model = modelBase;
            this->draw(VAOStaircaseSide, textureStaircaseSide, model, camera);


            model = glm::translate(model, glm::vec3(0.0, -1.5,0.0));
            this->draw(VAOUnderStaircase, textureUnderStaircase, model, camera);
            model = glm::translate(model, glm::vec3(0.0, 0.001,0.0));
            this->draw(VAOUnderStaircaseComplete, textureUnderStaircaseComplete, model, camera);


            model = modelBase;
            model = glm::translate(model, glm::vec3(0.0, 17.8,0.0));
            this->draw(VAOUnderStaircase, textureUnderStaircase, model, camera);
            model = glm::translate(model, glm::vec3(0.0, 0.001,0.0));
            this->draw(VAOUnderStaircaseComplete, textureUnderStaircaseComplete, model, camera);




            // The first
            model = modelBase;
            model = glm::translate(model, glm::vec3(-39.0, -2.0, -63.3));
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
            for (int i = 0; i <8; i++) {
                drawStaircase(camera, model);
                model = glm::translate(model, glm::vec3(0.0, 1.6, +1.5));
            }
            model = modelBase;
            model = glm::translate(model, glm::vec3(-43.0, 10.0, -55.0));
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

            for (int i = 0; i < 5; i++) {
                drawStaircase(camera, model);
                model = glm::translate(model, glm::vec3(0.0, 1.6, -1.5));
            }



            // The second
            model = modelBase;
            model = glm::translate(model, glm::vec3(-35.0, 17.6, -63.3));
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

            for (int i = 0; i <8; i++) {
                drawStaircase(camera, model);
                model = glm::translate(model, glm::vec3(0.0, 1.6, +1.5));
            }
            model = modelBase;
            model = glm::translate(model, glm::vec3(-43.0, 29.6, -55.0));
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

            for (int i = 0; i <3; i++) {
                drawStaircase(camera, model);
                model = glm::translate(model, glm::vec3(0.0, 1.6, -1.5));
            }


//            model = modelBase;
//            model = glm::translate(model, glm::vec3(-36.83, 17.0, -56.9));
//            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
//            drawStaircase(camera, model);
//
//            for (int i = 0; i < 10; i++) {
//                model = glm::translate(model, glm::vec3(0.0, 1.6, -1.5));
//                drawStaircase(camera, model);
//            }


        }
    }

    void drawStreet(Camera camera, glm::mat4 modelBase) {

        glm::mat4 modelHelper = glm::mat4(1.0);
        modelHelper = glm::rotate(modelHelper, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        modelHelper = glm::translate(modelHelper, glm::vec3(0.0, 16.6, 3.3));

        glm::mat4 model = modelHelper * modelBase;
        this->draw(VAOStreet, textureStreet, model, camera);
        model = glm::translate(model, glm::vec3(0.0, 20.0, -0.0));
        this->draw(VAOStreet, textureStreet, model, camera);
        model = glm::translate(model, glm::vec3(0.0, -13.33, -0.0));
        this->draw(VAOGrass, textureGrass, model, camera);

    }


    // رسم مع شفافيه
    void drawCutter(Camera camera, glm::mat4 modelBase) {
        // cutter right
        glm::mat4 model = modelBase;
        model = glm::translate(modelBase, glm::vec3(-2.0, 0.0, 0.0));
        this->draw(VAOCutter1Right, textureCutter1Right, model, camera);


        // cutter left
        model = glm::translate(modelBase, glm::vec3(-26.0, 0.0, 0.0));
        this->draw(VAOCutter1Right, textureCutter1Right, model, camera);


        // restaurant interface
        model = modelBase;
        model = glm::translate(model, glm::vec3(61.3, 0.0, 0.0));
        this->draw(VAOInterfaceRestaurant, textureInterfaceRestaurant, model, camera);

        // restaurant interface complete
        model = glm::translate(model, glm::vec3(1.2, 0.0, 0.0));
        this->draw(VAOInterfaceCompleteRestaurant, textureInterfaceCompleteRestaurant, model, camera);



        // To draw shelf left
        model = modelBase;
        model = glm::scale(model, glm::vec3(1.0, 1.0, 2.0));

        model = glm::translate(model, glm::vec3(61.3, 0.0, 4.0));
        model = glm::translate(model, glm::vec3(1.2, 0.0, 0.0));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0, -14.0, 27.0));


        this->draw(VAOInterfaceCompleteRestaurant, textureInterfaceCompleteRestaurant, model, camera);

        // To draw shelf right
        model = modelBase;
        model = glm::scale(model, glm::vec3(1.0, 1.0, 2.0));
        model = glm::translate(model, glm::vec3(61.3, 0.0, 4.0));
        model = glm::translate(model, glm::vec3(1.2, 0.0, 0.0));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0, -14.0, 27.0));
        model = glm::translate(model, glm::vec3(-34.5, 0.0, 0.0));
        this->draw(VAOInterfaceCompleteRestaurant, textureInterfaceCompleteRestaurant, model, camera);

        // To draw shelf front



    }

    void drawDoor(Camera camera, glm::mat4 modelBase) {
        drawCutter(camera, modelBase);

        if (-10 < camera.Position.x && camera.Position.x < 8 && -3 < camera.Position.y && camera.Position.y < 3.5 &&
            -10 < camera.Position.z && camera.Position.z < 12) {

            if (camera.Position.z < 0.0) {
                glm::mat4 model = modelBase;

                model = glm::translate(model, glm::vec3(10.0f, 0.0f, +10.0f));
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                this->draw(VAODoorRight, textureDoorRight, model, camera);


                model = modelBase;
                model = glm::translate(model, glm::vec3(-10.0f, 0.0f, +0.0f));
                model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(10.0f, 0.0f, +0.0f));

                this->draw(VAODoorLeft, textureDoorLeft, model, camera);
            } else {
                glm::mat4 model = modelBase;
                model = glm::translate(model, glm::vec3(10.0f, 0.0f, -10.0f));
                model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                this->draw(VAODoorRight, textureDoorRight, model, camera);


                model = modelBase;
                model = glm::translate(model, glm::vec3(-10.0f, 0.0f, +0.0f));
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(10.0f, 0.0f, +0.0f));

                this->draw(VAODoorLeft, textureDoorLeft, model, camera);

            }

        } else {
            glm::mat4 model = modelBase;
            this->draw(VAODoorRight, textureDoorRight, model, camera);
            this->draw(VAODoorLeft, textureDoorLeft, model, camera);
        }



//         model = modelBase;
//        if (-7 < camera.Position.x && camera.Position.x < 3 && -2.6 < camera.Position.y && camera.Position.y < 3.6 &&
//            -7.5 < camera.Position.z && camera.Position.z < 10) {
//            model = glm::translate(model, glm::vec3(5.0f, 0.0f, +5.0f));  // نقل إلى الطرف الأيسر
//            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));  // التدوير حول المحور Y
//            this->draw(VAODoorLeftBack, textureDoorLeft, model, camera);
//
//        }
//
//
//        this->draw(VAODoorLeftBack, textureDoorLeft, model, camera);

    }

    void drawShwarma(Camera camera, glm::mat4 modelBase) {

        ourShader.use();
        ourShader.setInt("texture", 0);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                                100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.use();
        glm::mat4 model = modelBase;
        model = glm::translate(model, glm::vec3(-44.0, 0.0, -26.0));

        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        ourShader.setMat4("model", model);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureShawarma);
        glBindVertexArray(VAOShawarma);
        glDrawElements(GL_TRIANGLES, 6 * 36, GL_UNSIGNED_INT, 0);
    }

private:
    void setVAO() {
        GLfloat right[] = {
                // positions          // colors           // texture coords
                15.0f, 15.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                15.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                3.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                3.0f, 15.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat left[] = {
                // positions          // colors           // texture coords
                -3.0f, 15.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                -3.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -15.0f, 15.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat center[] = {
                // positions          // colors           // texture coords
                3.0f, 15.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                3.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -3.0f, 2.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -3.0f, 15.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat doorRight[] = {
                // positions          // colors           // texture coords
                3.0f, 2.0f, -0.01f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                3.0f, -1.f, -0.01f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -0.0f, -1.0f, -0.01f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -0.0f, 2.0f, -0.01f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };

        GLfloat doorLeft[] = {
                // positions          // colors           // texture coords
                0.0f, 2.0f, -0.01f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                0.0f, -1.f, -0.01f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -3.0f, -1.0f, -0.01f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -3.0f, 2.0f, -0.01f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat top[] = {
                // positions          // colors           // texture coords
                15.0f, 15.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                15.0f, 8.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.0f, 8.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -15.0f, 15.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat wallRight[] = {
                // positions          // colors           // texture coords
                15.0f, 15.0f, -20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                15.0f, -1.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                15.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                15.0f, 15.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat wallLeft[] = {
                // positions          // colors           // texture coords
                -15.0f, 15.0f, -20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                -15.0f, -1.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -15.0f, 15.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat back[] = {
                // positions          // colors           // texture coords
                15.0f, 15.0f, -20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                15.0f, -1.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.0f, -1.0f, -20.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -15.0f, 15.0f, -20.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };

        GLfloat up[] = {
                // positions          // colors           // texture coords
                15.0f, 15.0f, -20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                15.0f, 15.0f, -0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.0f, 15.0f, -0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -15.0f, 15.0f, -20.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };

        GLfloat down[] = {
                // positions          // colors           // texture coords
                15.0f, -1.0f, -20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                15.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -15.0f, -1.0f, -20.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat street[] = {
                // positions          // colors           // texture coords
                25.0f, -1.0f, -0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                25.0f, -5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -35.0f, -5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -35.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };
        GLfloat grass[] = {
                // positions          // colors           // texture coords
                25.0f, -1.0f, -0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                25.0f, -3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -35.0f, -3.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -35.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        setStreet(VAOStreet, VBOStreet, EBO, textureStreet, street,
                  sizeof(wallLeft),
                  FileSystem::getPath("src/3.model_loading/images/street_lr.bmp").c_str());

        setStreet(VAOGrass, VBOGrass, EBO, textureGrass, grass,
                  sizeof(wallLeft),
                  FileSystem::getPath("src/3.model_loading/images/opengl_rt0.bmp").c_str());


        build(VAORight, VAORightBack, VBORight, VBORightBack, EBO, textureRight, right, sizeof(right),
              FileSystem::getPath("src/3.model_loading/images/right.png").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "front");

        build(VAOLeft, VAOLeftBack, VBOLeft, VBOLeftBack, EBO, textureLeft, left, sizeof(left),
              FileSystem::getPath("src/3.model_loading/images/right.png").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "front");

        build(VAOCenter, VAOCenterBack, VBOCenter, VBOCenterBack, EBO, textureCenter, center, sizeof(center),
              FileSystem::getPath("src/3.model_loading/images/Blur.png").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "front");

        build(VAODoorRight, VAODoorRightBack, VBODoorRight, VBODoorRightBack, EBO, textureDoorRight, doorRight,
              sizeof(doorRight),
              FileSystem::getPath("src/3.model_loading/images/doorRight.png").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "front");

        build(VAODoorLeft, VAODoorLeftBack, VBODoorLeft, VBODoorLeftBack, EBO, textureDoorLeft, doorLeft,
              sizeof(doorLeft),
              FileSystem::getPath("src/3.model_loading/images/doorLeft.jpg").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "front");





//        build(VAOTop, VAOTopBack, VBOTop, VBOTopBack, EBO, textureTop, top, sizeof(top),
//              FileSystem::getPath("src/3.model_loading/images/top2.png").c_str(),
//              FileSystem::getPath(TEXTUREBACK).c_str(), "front");

        build(VAOWallRight, VAOWallRightBack, VBOWallRight, VBOWallRightBack, EBO, textureWallRight, wallRight,
              sizeof(wallRight),
              FileSystem::getPath("src/3.model_loading/images/photo_2024-12-04_10-51-1ddd5.jpg").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "right");

        build(VAOWallLeft, VAOWallLeftBack, VBOWallLeft, VBOWallLeftBack, EBO, textureWallLeft, wallLeft,
              sizeof(wallLeft),
              FileSystem::getPath("src/3.model_loading/images/photo_2024-12-04_10-51-1ddd5.jpg").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "left");

        build(VAOBack, VAOBackBack, VBOBack, VBOBackBack, EBO, textureBackBack, back,
              sizeof(wallLeft),
              FileSystem::getPath("src/3.model_loading/images/photo_2024-12-04_10-51-1ddd5.jpg").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "back");

        build(VAOUp, VAOUpBack, VBOUp, VBOUpBack, EBO, textureUp, up,
              sizeof(wallLeft),
              FileSystem::getPath("src/3.model_loading/images/photo_2024-12-04_10-51-1ddd5.jpg").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "up");


        build(VAODown, VAODownBack, VBODown, VBODownBack, EBO, textureDown, down,
              sizeof(wallLeft),
              FileSystem::getPath("src/3.model_loading/images/photo_2024-12-04_10-51-1ddd5.jpg").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "down");


    }

    void setStreet(GLuint &VAO, GLuint &VBO, GLuint &EBO, GLuint &texture,
                   GLfloat *array,
                   GLsizeiptr size, const char *image) {

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
    }

    void setCutterAndFloor() {
        GLfloat wallRight[] = {
                // positions          // colors           // texture coords
                4.0f, 3.0f, -8.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                4.0f, -1.0f, -8.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                4.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                4.0f, 3.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };
        GLfloat floor1[] = {
                // positions          // colors           // texture coords
                15.0f, 10.0f, -15.5, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                15.0f, 10.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.0f, 10.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -15.0f, 10.0f, -15.5, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };

        GLfloat floor1Complete[] = {
                // positions          // colors           // texture coords
                10.0f, 10.0f, -20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                10.0f, 10.0f, -15.5, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -11.5, 10.0f, -15.5, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -11.5, 10.0f, -20.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat floor2[] = {
                // positions          // colors           // texture coords
                15.0f, 5.0f, -15.5, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                15.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -15.0f, 5.0f, -15.5, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };

        GLfloat floor2Complete[] = {
                // positions          // colors           // texture coords
                10.0f, 5.0f, -20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                10.0f, 5.0f, -15.5, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -10.6, 5.0f, -15.5, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -10.6, 5.0f, -20.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        setStreet(VAOCutter1Right, VBOCutter1Right, EBO, textureCutter1Right, wallRight,
                  sizeof(wallRight),
                  FileSystem::getPath("src/3.model_loading/images/blur2.png").c_str());

        setStreet(VAOFloor1, VBOFloor1, EBO, textureFloor1, floor1,
                  sizeof(floor1),
                  FileSystem::getPath("src/3.model_loading/images/Wood smg.bmp").c_str());

        setStreet(VAOFloor1Complete, VBOFloor1Complete, EBO, textureFloor1Complete, floor1Complete,
                  sizeof(floor1Complete),
                  FileSystem::getPath("src/3.model_loading/images/Wood smg.bmp").c_str());


        setStreet(VAOFloor2, VBOFloor2, EBO, textureFloor2, floor2,
                  sizeof(floor2),
                  FileSystem::getPath("src/3.model_loading/images/Wood smg.bmp").c_str());

        setStreet(VAOFloor2Complete, VBOFloor2Complete, EBO, textureFloor2Complete, floor2Complete,
                  sizeof(floor2Complete),
                  FileSystem::getPath("src/3.model_loading/images/Wood smg.bmp").c_str());


    }

    void setTableForChef() {

        GLfloat Interface[] = {
                // positions          // colors           // texture coords
                15.0f, 3.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                15.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                3.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                3.0f, 3.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        // for Res and Clothes
        GLfloat front[] = {
                // positions          // colors           // texture coords
                -15.0f, 3.0f, -8.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                -15.0f, -1.0f, -8.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -7.0f, -1.0f, -8.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -7.0f, 3.0f, -8.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };
        GLfloat frontComplete[] = {
                // positions          // colors           // texture coords
                -5.0f, 3.0f, -8.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                -5.0f, -1.0f, -8.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -3.77f, -1.0f, -8.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -3.77f, 3.0f, -8.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };
        setStreet(VAOInterfaceRestaurant, VBOInterfaceRestaurant, EBO, textureInterfaceRestaurant, front,
                  sizeof(front),
                  FileSystem::getPath("src/3.model_loading/images/clothes2.png").c_str());

        setStreet(VAOInterfaceCompleteRestaurant, VBOInterfaceCompleteRestaurant, EBO,
                  textureInterfaceCompleteRestaurant, frontComplete,
                  sizeof(frontComplete),
                  FileSystem::getPath("src/3.model_loading/images/clothes2.png").c_str());

        GLfloat table[] = {
                // positions          // colors           // texture coords
                -9.0f, 0.6f, -8.55f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                -9.0f, 0.6f, -6.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.0f, 0.6f, -6.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -15.0f, 0.6f, -8.55f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };
        setStreet(VAOTable, VBOTable, EBO, textureTable, table,
                  sizeof(table),
                  FileSystem::getPath("src/3.model_loading/images/grill2.png").c_str());


        GLfloat vertical[] = {
                // positions          // colors           // texture coords
                0.5f, 3.54f, -3.01f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                0.5f, 0.6f, -3.01f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -1.5f, 0.6f, -3.01f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -1.5f, 3.54f, -3.01f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };
        build(VAOVertical, VAOVerticalBack, VBOTVertical, VBOTVerticalBack, EBO, textureTVertical, vertical,
              sizeof(vertical),
              FileSystem::getPath("src/3.model_loading/images/fire2.png").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "front");

        GLfloat center[] = {
                // positions          // colors           // texture coords
                3.0f, 15.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                3.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -3.0f, 2.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -3.0f, 15.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat doorRight[] = {
                // positions          // colors           // texture coords
                3.0f, 2.0f, -0.01f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                3.0f, -1.f, -0.01f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -0.0f, -1.0f, -0.01f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -0.0f, 2.0f, -0.01f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };

        GLfloat doorLeft[] = {
                // positions          // colors           // texture coords
                0.0f, 2.0f, -0.01f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                0.0f, -1.f, -0.01f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -3.0f, -1.0f, -0.01f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -3.0f, 2.0f, -0.01f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat top[] = {
                // positions          // colors           // texture coords
                15.0f, 15.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                15.0f, 8.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.0f, 8.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -15.0f, 15.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat wallRight[] = {
                // positions          // colors           // texture coords
                15.0f, 15.0f, -20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                15.0f, -1.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                15.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                15.0f, 15.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat wallLeft[] = {
                // positions          // colors           // texture coords
                -15.0f, 15.0f, -20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                -15.0f, -1.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -15.0f, 15.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat back[] = {
                // positions          // colors           // texture coords
                15.0f, 15.0f, -20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                15.0f, -1.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.0f, -1.0f, -20.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -15.0f, 15.0f, -20.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };

        GLfloat up[] = {
                // positions          // colors           // texture coords
                15.0f, 15.0f, -20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                15.0f, 15.0f, -0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.0f, 15.0f, -0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -15.0f, 15.0f, -20.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


    }

    void banner() {

        GLfloat Restaurant[] = {
                // positions          // colors           // texture coords
                -15.0f, 5.0f, -8.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                -15.0f, 3.0f, -8.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -3.77, 3.0f, -8.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -3.77, 5.0f, -8.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };
        GLfloat RestaurantSide[] = {
                // positions          // colors           // texture coords
                -3.77, 5.0f, -8.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                -3.77, 3.0f, -8.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -3.77, 3.0f, -0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -3.77, 5.0f, -0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        GLfloat clothes[] = {
                // positions          // colors           // texture coords
                15.0, 5.0f, -8.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                15.0, 3.0f, -8.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                3.34, 3.0f, -8.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                3.34, 5.0f, -8.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };
        GLfloat clothesSide[] = {
                // positions          // colors           // texture coords
                3.34, 5.0f, -8.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                3.34, 3.0f, -8.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                3.34, 3.0f, -0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                3.34, 5.0f, -0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };


        build(VAOBannerRestaurant, VAOBannerRestaurantBack, VBOBannerRestaurant, VBOBannerRestaurantBack, EBO,
              textureBannerRestaurant, Restaurant, sizeof(Restaurant),
              FileSystem::getPath("src/3.model_loading/images/resturant.jpeg").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "back");

        build(VAOBannerRestaurantSide, VAOBannerRestaurantBackSide, VBOBannerRestaurantSide,
              VBOBannerRestaurantBackSide, EBO,
              textureBannerRestaurantSide, RestaurantSide, sizeof(RestaurantSide),
              FileSystem::getPath("src/3.model_loading/images/right.png").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "left");


        build(VAOBannerClothes, VAOBannerClothesBack, VBOBannerClothes, VBOBannerClothesBack, EBO,
              textureBannerClothes, clothes, sizeof(clothes),
              FileSystem::getPath("src/3.model_loading/images/v7pFeDH3.jpeg").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "back");


        build(VAOBannerClothesSide, VAOBannerClothesBackSide, VBOBannerClothesSide, VBOBannerClothesBackSide, EBO,
              textureBannerClothesSide, clothesSide, sizeof(clothesSide),
              FileSystem::getPath("src/3.model_loading/images/right.png").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "right");


    }

    void setShawarma() {
        generateConeMesh(1.0f, 0.2f, 2.0f);
    }

    void generateConeMesh(float topRadius, float bottomRadius,
                          float height) {
        const int SEGMENTS = 36;
        const int VERTEX_COUNT = (SEGMENTS + 1) * 2; // عدد الرؤوس
        const int INDEX_COUNT = SEGMENTS * 6;       // عدد الفهارس

        GLfloat vertices[VERTEX_COUNT * 5]; // كل رأس يحتوي على 5 قيم
        GLuint indices[INDEX_COUNT];

        float angleStep = 2.0f * M_PI / SEGMENTS;
        int vertexIndex = 0;
        int indexIndex = 0;


        for (int i = 0; i <= SEGMENTS; ++i) {
            float angle = i * angleStep;
            float x = bottomRadius * cos(angle);
            float z = bottomRadius * sin(angle);


            vertices[vertexIndex++] = x;
            vertices[vertexIndex++] = 0.0f;
            vertices[vertexIndex++] = z;
            vertices[vertexIndex++] = i / float(SEGMENTS);
            vertices[vertexIndex++] = 0.0f;
        }


        for (int i = 0; i <= SEGMENTS; ++i) {
            float angle = i * angleStep;
            float x = topRadius * cos(angle);
            float z = topRadius * sin(angle);


            vertices[vertexIndex++] = x;
            vertices[vertexIndex++] = height;
            vertices[vertexIndex++] = z;
            vertices[vertexIndex++] = i / float(SEGMENTS);
            vertices[vertexIndex++] = 1.0f;
        }


        for (int i = 0; i < SEGMENTS; ++i) {
            indices[indexIndex++] = i;
            indices[indexIndex++] = i + SEGMENTS + 1;
            indices[indexIndex++] = i + 1;

            indices[indexIndex++] = i + 1;
            indices[indexIndex++] = i + SEGMENTS + 1;
            indices[indexIndex++] = i + SEGMENTS + 2;
        }

        glGenVertexArrays(1, &VAOShawarma);
        glGenBuffers(1, &VBOShawarma);
        glGenBuffers(1, &EBOShawarma);

        glBindVertexArray(VAOShawarma);

        glBindBuffer(GL_ARRAY_BUFFER, VBOShawarma);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOShawarma);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // تحديد تخطيط البيانات
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);


        glGenTextures(1, &textureShawarma);
        glBindTexture(GL_TEXTURE_2D, textureShawarma);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int widthTexture, heightTexture, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char *data = stbi_load(
                FileSystem::getPath("src/3.model_loading/images/shawarma.png").c_str(), &widthTexture,
                &heightTexture, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthTexture, heightTexture, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    void setBlouse() {
        GLfloat body[] = {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                          0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                          0.5f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                          -0.5f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        };

        GLfloat left[]{
                -0.8f, -0.3f, 0.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f,
                -0.6f, -0.3f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f, 0.0f,
                -0.6f, 0.7f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f, 1.0f,
                -0.8f, 0.7f, 0.0f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f,
        };

        GLfloat leftComplete[]{
                -0.5f, 0.7f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                -0.5f, 0.25f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                -0.6f, 0.25f, 0.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f,
                -0.6f, 0.7f, 0.0f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f,


        };

        GLfloat right[]{
                0.6f, -0.3f, 0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
                0.8f, -0.3f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
                0.8f, 0.7f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
                0.6f, 0.7f, 0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
        };
        GLfloat rightComplete[]{
                0.6f, 0.7f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
                0.6f, 0.25f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
                0.5f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.5f, 0.7f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        };

        GLfloat collar[]{
                -0.2f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.2f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                0.2f, 0.8f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                -0.2f, 0.8f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f

        };

        build(VAOBlouseBody, VAOBlouseBodyBack, VBOBlouseBody, VBOBlouseBodyBack, EBO, textureBlouseBody, body,
              sizeof(body),
              FileSystem::getPath("src/3.model_loading/images/right.png").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "front");

        build(VAOBlouseLeft, VAOBlouseLeftBack, VBOBlouseLeft, VBOBlouseLeftBack, EBO, textureBlouseLeft, left,
              sizeof(left),
              FileSystem::getPath("src/3.model_loading/images/right.png").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "front");

        setStreet(VAOBlouseLeftComplete, VBOBlouseLeftComplete, EBO, textureBlouseLeftComplete, leftComplete,
                  sizeof(leftComplete),
                  FileSystem::getPath("src/3.model_loading/images/opengl_rt0.bmp").c_str());


        build(VAOBlouseRight, VAOBlouseRightBack, VBOBlouseRight, VBOBlouseRightBack, EBO, textureBlouseRight, right,
              sizeof(right),
              FileSystem::getPath("src/3.model_loading/images/right.png").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "front");

        setStreet(VAOBlouseRightComplete, VBOBlouseRightComplete, EBO, textureBlouseRightComplete, rightComplete,
                  sizeof(rightComplete),
                  FileSystem::getPath("src/3.model_loading/images/opengl_rt0.bmp").c_str());


        build(VAOBlouseCollar, VAOBlouseCollarBack, VBOBlouseCollar, VBOBlouseCollarBack, EBO, textureBlouseCollar,
              collar, sizeof(collar),
              FileSystem::getPath("src/3.model_loading/images/right.png").c_str(),
              FileSystem::getPath(TEXTUREBACK).c_str(), "front");
        {
            float sweaterVertices[] = {

                    // Positions          // Texture Coords
                    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                    0.5f, 0.7f, 0.0f, 1.0f, 1.0f,
                    -0.5f, 0.7f, 0.0f, 0.0f, 1.0f,

                    -0.7f, 0.4f, 0.0f, 0.0f, 0.0f,
                    -0.5f, 0.4f, 0.0f, 1.0f, 0.0f,
                    -0.5f, 0.7f, 0.0f, 1.0f, 1.0f,
                    -0.7f, 0.7f, 0.0f, 0.0f, 1.0f,

                    0.5f, 0.4f, 0.0f, 0.0f, 0.0f,
                    0.7f, 0.4f, 0.0f, 1.0f, 0.0f,
                    0.7f, 0.7f, 0.0f, 1.0f, 1.0f,
                    0.5f, 0.7f, 0.0f, 0.0f, 1.0f,

                    -0.2f, 0.7f, 0.0f, 0.0f, 0.0f,
                    0.2f, 0.7f, 0.0f, 1.0f, 0.0f,
                    0.2f, 0.8f, 0.0f, 1.0f, 1.0f,
                    -0.2f, 0.8f, 0.0f, 0.0f, 1.0f
            };
        }

    }

    void drawBlouse(Camera camera, glm::mat4 model, GLuint textureBody, GLuint textureLeft, GLuint textureRight,
                    GLuint textureCollar) {
        this->draw(VAOBlouseBody, textureBody, model, camera);


        this->draw(VAOBlouseLeft, textureLeft, model, camera);
        this->draw(VAOBlouseLeftComplete, textureLeft, model, camera);
        this->draw(VAOBlouseRight, textureRight, model, camera);
        this->draw(VAOBlouseRightComplete, textureRight, model, camera);
        this->draw(VAOBlouseCollar, textureCollar, model, camera);


    }

    void setPants() {

        GLfloat left[] = {
                -0.0f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                -0.2f, -2.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
                -1.0f, -2.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                -1.0f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,


        };
        GLfloat right[] = {1.0f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                           1.0f, -2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                           0.2f, -2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                           0.0f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        };
        GLfloat belt[] = {1.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f, 1.0f, 1.0f,
                          1.0f, -0.2f, 0.0f, 0.8f, 0.8f, 0.0f, 1.0f, 0.0f,
                          -1.0f, -0.2f, 0.0f, 0.8f, 0.8f, 0.0f, 0.0f, 0.0f,
                          -1.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f, 0.0f, 1.0f
        };


//        setStreet(VAOPantsBody, VBOPantsBody, EBO, texturePantsBody, body,
//                  sizeof(bool),
//                  FileSystem::getPath("src/3.model_loading/images/opengl_rt0.bmp").c_str());


        setStreet(VAOPantsLeft, VBOPantsLeft, EBO, texturePantsLeft, left,
                  sizeof(left),
                  FileSystem::getPath("src/3.model_loading/images/opengl_rt0.bmp").c_str());


        setStreet(VAOPantsRight, VBOPantsRight, EBO, texturePantsRight, right,
                  sizeof(right),
                  FileSystem::getPath("src/3.model_loading/images/opengl_rt0.bmp").c_str());


        setStreet(VAOPantsBelt, VBOPantsBelt, EBO, texturePantsBelt, belt,
                  sizeof(belt),
                  FileSystem::getPath("src/3.model_loading/images/opengl_rt0.bmp").c_str());


    }

    void drawPants(Camera camera, glm::mat4 model, GLuint textureLeft, GLuint textureRight,
                   GLuint textureBelt) {
//        this->draw(VAOPantsBody, textureBody, model, camera);
        this->draw(VAOPantsLeft, textureLeft, model, camera);
        this->draw(VAOPantsRight, textureRight, model, camera);
        this->draw(VAOPantsBelt, textureBelt, model, camera);
    }

    void setStaircase() {
        GLfloat staircase[] = {
                1.0f, 0.25f, 0.0f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
                1.0f, -0.25f, -0.0f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
                -1.0f, -0.25f, -0.0f, 0.0, 0.0, 0.0, 0.0f, 0.0f,
                -1.0f, 0.25f, -0.0f, 0.0, 0.0, 0.0, 0.0f, 0.0f,

                1.0f, 0.25f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
                1.0f, -0.25f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
                -1.0f, -0.25f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,
                -1.0f, 0.25f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,

        };

        GLuint indices[] = {
                0, 1, 2, 0, 2, 3,
                4, 5, 6, 4, 6, 7,
                3, 2, 6, 3, 6, 7,
                0, 1, 5, 0, 5, 4,
                1, 2, 6, 1, 6, 5,
                0, 3, 7, 0, 7, 4
        };

        GLfloat staircaseSide[] = {
                // positions          // colors           // texture coords
                -11.0, 10.0f, -15.46, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                -11.0, -1.0f, -15.46, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.00, -1.0f, -15.46, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -15.0, 10.0f, -15.46, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };

        GLfloat underStaircase[] = {
                // positions          // colors           // texture coords
                -14.0, 3.5f, -20.0, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.0f, 3.5f, -20.0, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                -15.0f, 3.5f, -15.46f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -14.0, 3.5f, -15.46f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };

        GLfloat underStaircaseComplete[] = {
                // positions          // colors           // texture coords
                -13.0, 3.5f, -17.46, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -15.0f, 3.5f, -17.46, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                -15.0f, 3.5f, -15.46f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -13.0, 3.5f, -15.46f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };

        buildSetStaircase(VAOStaircase, VBOStaircase, EBOStaircase, indices, sizeof(indices), textureStaircase,
                          staircase,
                          sizeof(staircase));

        setStreet(VAOStaircaseSide, VBOStaircaseSide, EBOStaircase, textureStaircaseSide, staircaseSide,
                  sizeof(staircaseSide),
                  FileSystem::getPath("src/3.model_loading/images/Wood smg.bmp").c_str());

        setStreet(VAOUnderStaircase, VBOUnderStaircase, EBO, textureUnderStaircase, underStaircase,
                  sizeof(underStaircase),
                  FileSystem::getPath("src/3.model_loading/images/Wood smg.bmp").c_str());

        setStreet(VAOUnderStaircaseComplete, VBOUnderStaircaseComplete, EBO, textureUnderStaircaseComplete, underStaircaseComplete,
                  sizeof(underStaircaseComplete),
                  FileSystem::getPath("src/3.model_loading/images/Wood smg.bmp").c_str());



    }

    void
    buildSetStaircase(GLuint &VAO, GLuint &VBO, GLuint &EBO, GLuint *indices, GLsizeiptr sizeIndex, GLuint &texture,
                      GLfloat *staircase,
                      GLsizeiptr size) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, size, staircase, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndex, indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);  // Positions
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));  // Colors
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                              (void *) (6 * sizeof(float)));  // Texture Coords
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }

    void drawStaircase(Camera camera, glm::mat4 model) {
        ourShader.use();
        ourShader.setInt("texture", 0);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                                100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.use();

        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        ourShader.setMat4("model", model);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureStaircase);
        glBindVertexArray(VAOStaircase);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
};

#endif //LEARNOPENGL_MALLBUILDER_H
