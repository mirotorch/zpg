#pragma once

#include "scene.h"
#include "../models/sphere.h"
#include "glm/gtc/matrix_transform.hpp"


class SphereScene : public Scene
{
    void UpdateTransformations() override
    {
        drawable_objects[0]->transformation = 
        glm::rotate(drawable_objects[0]->transformation, glm::radians(1.0f), glm::vec3(1,0,0));
    }
    
    void CreateDrawableObjects() override
    {
        SetAsCurrent();
        Sphere* sphere = new Sphere();
        auto do_triangle = std::make_shared<DrawableObject>();
        do_triangle->model = sphere;
        do_triangle->transformation = glm::mat4(1.0f);
        do_triangle->shader = shader_factory->GetShader("normale_v", "normale_f");
        drawable_objects.push_back(do_triangle);
    }
public:
    SphereScene(std::string shader_path, int width, int height, const char* title) 
        : Scene(shader_path, width, height, title)
    {
        
    }
};