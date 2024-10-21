#pragma once

#include "model.h"
#include "transformation.h"
#include "shaderProgram.h"


class DrawableObject
{
public:
    Model* model;
    ShaderProgram* shader;
    Transformation* t_model;
    void Draw();
    ~DrawableObject();
};