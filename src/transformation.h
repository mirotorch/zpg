#pragma once

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

class Transformation
{
public:
    virtual glm::mat4 apply(glm::mat4 mat) = 0;
};

class Rotation : public Transformation 
{
    float radians;
    glm::vec3 direction;
public:
    Rotation(float radians, glm::vec3 direction);
    glm::mat4 apply(glm::mat4 mat) override;
};

class Translation : public Transformation
{
    glm::vec3 direction;
public:
    Translation(glm::vec3 direction);
    glm::mat4 apply(glm::mat4 mat) override;
};

class Scaling : public Transformation
{
    glm::vec3 scale;
public:
    Scaling(glm::vec3 scale);
    glm::mat4 apply(glm::mat4 mat) override;
};

class CompoundTransformation : public Transformation
{
    std::vector<Transformation*> transformations;
public:
    CompoundTransformation();
    CompoundTransformation(std::vector<Transformation*> transformations);
    ~CompoundTransformation();
    void Add(Transformation* t);
    void Pop();
    glm::mat4 apply(glm::mat4 mat) override;
};