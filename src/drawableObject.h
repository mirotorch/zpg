#pragma once

#include "model.h"
#include "transformation.h"
#include "shaderProgram.h"


class DrawableObject
{
public:
    Model* model;
    ShaderProgram* shader;
    Transformation* transformation;
    Material material;
    void Draw();
    ~DrawableObject();
};