#pragma once

#include <glm/vec3.hpp>

#define MAX_LIGHTS 4

struct Light {
    glm::vec3 position;
    glm::vec3 color;

    float constant;
    float linear;
    float quadratic;
};