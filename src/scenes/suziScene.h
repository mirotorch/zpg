#pragma once

#include "scene.h"

class SuziScene : public Scene
{
public:
    SuziScene(std::string shader_path, GLFWwindow* window);
    void CreateDrawableObjects() override;
};