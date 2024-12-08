#pragma once

#include <glm/mat4x4.hpp>

class ICameraObserver
{
public:
    virtual void UpdateView(glm::mat4 view, glm::vec3 center, glm::vec3 eye) = 0;
    virtual void UpdateProjectionMatrix(glm::mat4 projection) = 0;
};