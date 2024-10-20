#pragma once

#include "scene.h"
#include "../models/bushes.h"
#include "../models/tree.h"
#include <GLFW/glfw3.h>

#include "glm/gtc/matrix_transform.hpp"

class ForestScene : public Scene
{
    void UpdateTransformations() override;
    void CreateTree(Transformation* t);
    void CreateBushes(Transformation* t);
    void CreateDrawableObjects() override;
    virtual void HandleKeyboardInput(int key, int scancode, int action, int mods);

public:
    ForestScene(std::string shader_path, int width, int height, const char *title);
};