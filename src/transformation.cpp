#include "transformation.h"

Rotation::Rotation(float radians, glm::vec3 direction)
{
    this->radians = radians;
    this->direction = direction;
}

glm::mat4 Rotation::apply(glm::mat4 mat)
{
    return glm::rotate(mat, radians, direction);
}

Translation::Translation(glm::vec3 direction)
{
    this->direction = direction;
}

glm::mat4 Translation::apply(glm::mat4 mat)
{
    return glm::translate(mat, direction);
}

Scaling::Scaling(glm::vec3 scale)
{
    this->scale = scale;
}

glm::mat4 Scaling::apply(glm::mat4 mat)
{
    return glm::scale(mat, scale);
}


CompoundTransformation::CompoundTransformation(std::vector<Transformation*> transformations)
{
    this->transformations = transformations;
}

CompoundTransformation::~CompoundTransformation()
{
    for (auto t : transformations) 
    {
        delete t;
    }
}

void CompoundTransformation::Pop()
{
    transformations.pop_back();
}

void CompoundTransformation::Add(Transformation * t)
{
    transformations.push_back(t);
}

glm::mat4 CompoundTransformation::apply(glm::mat4 mat)
{
    for (auto t : transformations)
    {
        mat = t->apply(mat);
    }
    return mat;
}
