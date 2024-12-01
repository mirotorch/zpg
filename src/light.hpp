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

    PointLight();
    PointLight(glm::vec3 position, glm::vec3 color, float constant, float linear, float quadratic);
};

#define MAX_DIR_LIGHTS 2

struct DirLight 
{
    glm::vec3 direction;
    glm::vec3 color;

    DirLight();
    DirLight(glm::vec3 direction, glm::vec3 color);
};


#define MAX_SPOTLIGHTS 2

struct Spotlight
{
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;
    float cutoff;
    float outerCutoff;

    float constant;
    float linear;
    float quadratic;
};

#endif