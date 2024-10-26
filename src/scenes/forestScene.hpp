#pragma once

#include "dynamicScene.h"
#include "../models/bushes.h"
#include "../models/tree.h"
#include <GLFW/glfw3.h>

#include "glm/gtc/matrix_transform.hpp"

class ForestScene : public DynamicScene
{
    void UpdateTransformations() override;
    void CreateDrawableObjects() override;
    void SetupCamera() override;
    void CreateForest(int trees, int bushes);
    void SaveDrawableObject(Transformation* ct, bool is_tree);
public:
    ForestScene(std::string shader_path, int width, int height, const char *title);
};