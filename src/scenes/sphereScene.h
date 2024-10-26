#pragma once

#include "scene.h"

class SphereScene : public Scene
{
    void UpdateTransformations() override;
    void CreateDrawableObjects() override;
    void SetupCamera() override;
public:
    SphereScene(std::string shader_path, int width, int height, const char* title);
};