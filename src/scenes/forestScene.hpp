#pragma once

#include "scene.h"
#include "../models/bushes.h"
#include "../models/tree.h"
#include <GLFW/glfw3.h>

#include "glm/gtc/matrix_transform.hpp"

class ForestScene : public Scene
{
    void UpdateTransformations() override;
    void CreateDrawableObjects() override;
    void CreateForest(int trees, int bushes);
    void SaveDrawableObject(Transformation* ct, bool is_tree);
    virtual void HandleKeyboardInput(int key, int scancode, int action, int mods);
    virtual void HandleMouseInput(double xpos, double ypos);

    float last_y;
    float last_x;
    bool first_mouse = true;
    const float rotation_speed = 0.1f;
public:
    ForestScene(std::string shader_path, int width, int height, const char *title);
};