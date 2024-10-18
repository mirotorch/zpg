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

    void CreateTree(Transformation* t)
    {
        auto drawable = new DrawableObject();
        drawable->model = new Tree();
        drawable->shader = shader_factory->GetShader("camera_v", "normale_f");
        drawable->t_model = t;
        drawable_objects.push_back(drawable);
    }

    void CreateBushes(Transformation* t)
    {
        auto drawable = new DrawableObject();
        drawable->model = new Bushes();
        drawable->shader = shader_factory->GetShader("camera_v", "green_f");
        drawable->t_model = t;
        drawable_objects.push_back(drawable);
    }

    void CreateDrawableObjects() override
    {
        SetAsCurrent();

        CompoundTransformation* ct1 = new CompoundTransformation(std::vector<Transformation*>({
            new Translation(glm::vec3(-0.8f, -1, 0)), 
            new Scaling(glm::vec3(0.2f, 0.2f, 0.2f))
        }));
        CreateTree(ct1);

        CompoundTransformation* ct2 = new CompoundTransformation(std::vector<Transformation*>({
            new Translation(glm::vec3(0, -1, 0)), 
            new Scaling(glm::vec3(0.2f, 0.2f, 0.2f)),
            new Rotation(glm::radians(60.0f), glm::vec3(0,1,0))
        }));
        CreateTree(ct2);

        // glm::mat4 mat3 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.4f, -0.99f, 0.0f));
        // CreateBushes(mat3);

        // glm::mat4 mat4 = glm::translate(glm::mat4(1.0f), glm::vec3(0.08f, -0.99f, 0.0f));
        // mat4 = glm::rotate(mat4, glm::radians(-30.0f), glm::vec3(0,0,1));
        // mat4 = glm::scale(mat4, glm::vec3(0.7f, 0.7f, 0.7f));
        // CreateBushes(mat4);
    }

public:
    ForestScene(std::string shader_path, int width, int height, const char *title)
        : Scene(shader_path, width, height, title)
    {
    }
};