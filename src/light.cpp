#include "light.hpp"

PointLight::PointLight()
{
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color, float constant, float linear, float quadratic)
{
    this->position = position;
    this->color = color;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}

DirLight::DirLight()
{
}

DirLight::DirLight(glm::vec3 direction, glm::vec3 color)
{
    this->direction = direction;
    this->color = color;
}
