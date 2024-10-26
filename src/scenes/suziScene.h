#pragma once

#include "dynamicScene.h"

class SuziScene : public DynamicScene
{
    void UpdateTransformations() override;
    void CreateDrawableObjects() override;
    void SetupCamera() override;
public:
    SuziScene(std::string shader_path, int width, int height, const char* title);
};