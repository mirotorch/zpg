#pragma once

#include "scene.h"

class ShadingTestScene : public Scene
{
    std::string shader_type;
public:
    ShadingTestScene(std::string shader_path, GLFWwindow* window, std::string shader_type);
    void CreateDrawableObjects() override;
};