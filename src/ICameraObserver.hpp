#pragma once

#include <glm/mat4x4.hpp>

class ICameraObserver
{
public:
    virtual void UpdateViewMatrix(glm::mat4 view) = 0;
    virtual void UpdateViewVector(glm::vec3 view) = 0;
    virtual void UpdateProjectionMatrix(glm::mat4 projection) = 0;
};