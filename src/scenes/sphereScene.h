#pragma once

#include "scene.h"

class SphereScene : public Scene
{
public:
    SphereScene(std::string shader_path, GLFWwindow* window);
    void CreateDrawableObjects() override;
    void HandleMouseButtonInput(double x_pos, double y_pos, int button) override;
    void Draw() override;
};