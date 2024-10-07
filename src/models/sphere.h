#pragma once

#include "model.h"
#include "../cv3_headers/sphere.h"

class Sphere : public Model
{
public:
    void Draw(Shader *shader, glm::vec4 transformation) override;
    Sphere();
};