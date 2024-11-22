#ifndef LIGHT
#define LIGHT

#include <glm/vec3.hpp>

#define MAX_POINT_LIGHTS 4

struct PointLight 
{
    glm::vec3 position;
    glm::vec3 color;

    float constant;
    float linear;
    float quadratic;
};

static PointLight NewPointLight(glm::vec3 position, glm::vec3 color, float constant, float linear, float quadratic)
{
    PointLight l;
    l.position = position;
    l.color = color;
    l.constant = constant;
    l.linear = linear;
    l.quadratic = quadratic;
    return l;
}

#define MAX_DIR_LIGHTS 2

struct DirLight 
{
    glm::vec3 direction;
    glm::vec3 color;
};

#endif