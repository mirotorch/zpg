#pragma once

#include "scene.h"
#include "../models/triangle.h"

class TestScene : public Scene
{
    void UpdateTransformations() override
    {
        
    }
    void CreateDrawableObjects() override
    {
        SetAsCurrent();
        Triangle* triangle = new Triangle(Point(1.0f, 1.0f, 1.0f), Point(0.5f, 0.0f, 0.5f), Point(0.0f, 0.5f, 0.0f));
        auto do_triangle = std::make_shared<DrawableObject>();
        do_triangle->model = triangle;
        do_triangle->transformation = glm::mat4(1.0f);
        do_triangle->shader = shader_factory->GetShader("triangle_v", "triangle_f");
        drawable_objects.push_back(do_triangle);
    }
public:
    TestScene(ShaderFactory* shader_factory, int width, int height, const char* title) 
        : Scene(shader_factory, width, height, title)
    {
        
    }
};