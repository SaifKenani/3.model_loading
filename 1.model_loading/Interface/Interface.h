//
// Created by saif on 1/12/25.
//

#ifndef LEARNOPENGL_INTERFACE_H
#define LEARNOPENGL_INTERFACE_H

#include "Polygon/Polygon.h"
#include "learnopengl/camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "learnopengl/camera.h"
#include "learnopengl/filesystem.h"

Polygon *polygon;

class Interface : public Polygon {


    Shader *shader;
    glm::vec3 cubePositions[10] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
    };
    GLfloat vertices[32] =
            { //     COORDINATES     /        COLORS      /   TexCoord  //
                    -0.9f, 0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Lower left corner
                    -0.9f, -0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Upper left corner
                    -0.3f, -0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Upper right corner
                    -0.3f, 0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f  // Lower right corner
            };
public:
    Interface() {
        polygon = new Polygon(vertices, sizeof(vertices),
                              FileSystem::getPath("resources/textures/brickwall_normal.jpg").c_str());


    }

    void DrawRightAndLeft(Camera camera, glm::mat4 baseModel) {
        float width = 0.6f;
        float height = 0.6f;
        int rows = 20;
        int cols = 20;


        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                glm::mat4 model = glm::mat4(1.0f);

                model = glm::translate(baseModel, glm::vec3(col * width, (row * height - 4.0f), -1.0f)); // ضبط المواقع

                polygon->Drow(camera, model);
            }
        }
    }


    void DrawWithDoor(Camera camera, glm::mat4 baseModel) {

        glm::mat4 model=glm::mat4 (1.0);
        model = glm::scale(model, glm::vec3(25.0f, 50.0f, 1.0f));
        model=model*baseModel;

        polygon->Drow(camera,model);

        model = glm::translate(model,glm::vec3( -1.0,0.0,0.0));
        polygon->Drow(camera,model);


        model=glm::mat4 (1.0);
        model = glm::scale(model, glm::vec3(17.0f, 30.0f, 1.0f));
        model=model*baseModel;
        polygon->Drow(camera,model);



    }


public:

};


#endif //LEARNOPENGL_INTERFACE_H
