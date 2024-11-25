#pragma once

#include "scene.h"

class TextureScene : public Scene
{
public:
    TextureScene(std::string shader_path, GLFWwindow* window);
    void CreateDrawableObjects() override;
};