#pragma once

#include "scene.h"

class SphereScene : public Scene
{
    void UpdateTransformations() override;
    void CreateDrawableObjects() override;
    void SetupCamera() override;
    void HandleKeyboardInput(int key, int scancode, int action, int mods) override;
    void HandleMouseInput(double xpos, double ypos) override;
public:
    SphereScene(std::string shader_path, int width, int height, const char* title);
};