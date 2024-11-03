#pragma once

#include "scene.h"
#include "../models/bushes.h"
#include "../models/tree.h"
#include <GLFW/glfw3.h>

#include "glm/gtc/matrix_transform.hpp"

class ForestScene : public Scene
{
    void CreateForest(int trees, int bushes);
    void SaveDrawableObject(Transformation* ct, bool is_tree);
public:
    ForestScene(std::string shader_path, GLFWwindow* window);
    void CreateDrawableObjects() override;
};