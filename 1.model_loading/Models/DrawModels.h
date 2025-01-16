//
// Created by saif on 1/15/25.
#include <learnopengl/model.h>
#include "learnopengl/filesystem.h"
#include "learnopengl/camera.h"
#include "learnopengl/shader_m.h"

#ifndef LEARNOPENGL_DRAWMODELS_H
#define LEARNOPENGL_DRAWMODELS_H

class DrawModels {
    Shader shader;
    Model Table;
    const unsigned int SCR_WIDTH = 1920;
    const unsigned int SCR_HEIGHT = 1080;

public:
    void drawTable(Camera camera, glm::mat4 baseModel) {

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                                100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);


        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-45.0, -1.0, -5.5));
        model = glm::scale(model, glm::vec3(5.0f, 5.0, 5.0));
        model = model * baseModel;
        shader.setMat4("model", model);
        Table.Draw(shader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-20.0, -1.0, -5.5));
        model = glm::scale(model, glm::vec3(5.0f, 5.0, 5.0));
        model = model * baseModel;
        shader.setMat4("model", model);
        Table.Draw(shader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-32.5, -1.0, -5.5));
        model = glm::scale(model, glm::vec3(5.0f, 5.0, 5.0));
        model = model * baseModel;
        shader.setMat4("model", model);
        Table.Draw(shader);


    }

    DrawModels() : Table(FileSystem::getPath("src/3.model_loading/models/simple_dining_table/scene.gltf")),
                   shader("1.model_loading.vs", "1.model_loading.fs") {

    }
};

#endif //LEARNOPENGL_DRAWMODELS_H
