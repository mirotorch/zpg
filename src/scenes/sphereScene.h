#pragma once

#include "scene.h"

class SphereScene : public Scene
{
public:
    SphereScene(std::string shader_path, GLFWwindow* window);
    void CreateDrawableObjects() override;
};