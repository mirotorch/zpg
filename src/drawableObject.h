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
    void Draw();
    ~DrawableObject();
};