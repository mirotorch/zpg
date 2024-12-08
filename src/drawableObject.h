#pragma once

#include "model.h"
#include "transformation.h"
#include "shaderProgram.h"
#include "movement/movement.hpp"

class DrawableObject
{
public:
    DrawableObject();
    DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation, Material material, GLuint texture_unit = -1);
    Model* model;
    ShaderProgram* shader;
    Transformation* transformation = nullptr;
    Movement* movement = nullptr;
    Material material;
    GLuint texture_unit = -1;
    void Draw();
    ~DrawableObject();
};