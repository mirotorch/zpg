#pragma once

#include "scene.h"
#include "../models/bushes.h"
#include "../models/tree.h"
#include "../skybox.h"
#include <GLFW/glfw3.h>

#include "glm/gtc/matrix_transform.hpp"

class SkyboxScene : public Scene
{
public:
    SkyboxScene(std::string shader_path, GLFWwindow* window);
    void CreateDrawableObjects() override;
};