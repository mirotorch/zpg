#pragma once

#include "model.h"
#include "transformation.h"
#include "shaderProgram.h"
#include "movement/movement.hpp"

class DrawableObject
{
    static int cnt;
    int id;
public:
    DrawableObject();
    DrawableObject(Model* model, ShaderProgram* shader,
     Transformation* transformation, Material material, GLuint texture_unit = 0, Movement* movement = nullptr);
    Model* model;
    ShaderProgram* shader;
    Transformation* transformation = nullptr;
    Movement* movement = nullptr;
    Material material;
    GLuint texture_unit = 0;
    void Draw();
    int GetId();
    ~DrawableObject();
};