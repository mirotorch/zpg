#pragma once

#include "model.h"
#include "transformation.h"
#include "shaderProgram.h"
#include "movement/movement.hpp"

class DrawableObject
{
public:
    DrawableObject();
    // DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation, Material material, GLuint texture_unit = 0);
    DrawableObject(Model* model, ShaderProgram* shader,
     Transformation* transformation, Material material, GLuint texture_unit = 0, Movement* movement = nullptr);
    Model* model;
    ShaderProgram* shader;
    Transformation* transformation = nullptr;
    Movement* movement = nullptr;
    Material material;
    GLuint texture_unit = 0;
    void Draw();
    ~DrawableObject();
};