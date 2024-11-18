#ifndef LIGHT
#define LIGHT

#include <glm/vec3.hpp>

#define MAX_LIGHTS 4

struct Light {
    glm::vec3 position;
    glm::vec3 color;

    float constant;
    float linear;
    float quadratic;
};

static Light NewLight(glm::vec3 position, glm::vec3 color, float constant, float linear, float quadratic)
{
    Light l;
    l.position = position;
    l.color = color;
    l.constant = constant;
    l.linear = linear;
    l.quadratic = quadratic;
    return l;
}

#endif