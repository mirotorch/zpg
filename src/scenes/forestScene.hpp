#pragma once

#include "scene.h"
#include "../models/tree.h"
#include "../models/bushes.h"
#include "glm/gtc/matrix_transform.hpp"

class ForestScene : public Scene
{
    void UpdateTransformations() override
    {
    }

    void CreateTree(glm::mat4 mat)
    {
        auto drawable = std::make_shared<DrawableObject>();
        drawable->model = new Tree();
        drawable->shader = shader_factory->GetShader("normale_v", "normale_f");
        drawable->transformation = mat;
        drawable_objects.push_back(drawable);
    }

    void CreateBushes(glm::mat4 mat)
    {
        auto drawable = std::make_shared<DrawableObject>();
        drawable->model = new Bushes();
        drawable->shader = shader_factory->GetShader("normale_v", "green_f");
        drawable->transformation = mat;
        drawable_objects.push_back(drawable);
    }

    void CreateDrawableObjects() override
    {
        SetAsCurrent();

        glm::mat4 mat1 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.8, -1, 0));
        mat1 = glm::scale(mat1, glm::vec3(0.2, 0.2, 0.2));
        CreateTree(mat1);


        glm::mat4 mat2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, -1, 0));
        mat2 = glm::scale(mat2, glm::vec3(0.2, 0.2, 0.2));
        mat2 = glm::rotate(mat2, glm::radians(60.0f), glm::vec3(0,1,0));
        CreateTree(mat2);

        glm::mat4 mat3 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.4f, -0.99f, 0.0f));
        CreateBushes(mat3);

        glm::mat4 mat4 = glm::translate(glm::mat4(1.0f), glm::vec3(0.08f, -0.99f, 0.0f));
        mat4 = glm::rotate(mat4, glm::radians(-30.0f), glm::vec3(0,0,1));
        mat4 = glm::scale(mat4, glm::vec3(0.7f, 0.7f, 0.7f));
        CreateBushes(mat4);
    }

public:
    ForestScene(std::string shader_path, int width, int height, const char *title)
        : Scene(shader_path, width, height, title)
    {
    }
};