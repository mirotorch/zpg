#pragma once

#include "scene.h"

class ShadingTestScene : public Scene
{
    std::string shader_type;
    void UpdateTransformations() override;
    void CreateDrawableObjects() override;
    void SetupCamera() override;
public:
    ShadingTestScene(std::string shader_type, std::string shader_path, int width, int height, const char* title);
};