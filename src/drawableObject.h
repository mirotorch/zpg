#pragma once
#include "models/model.h"
#include "transformation.h"


class DrawableObject
{
public:
    Model* model;
    ShaderProgram* shader;
    Transformation* t_model;
    Transformation* t_view;
    Transformation* t_projection;
    void Draw();
    ~DrawableObject();
};