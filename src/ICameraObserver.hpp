#pragma once

#include <glm/mat4x4.hpp>

class ICameraObserver
{
public:
    virtual void UpdateView(glm::mat4 view) = 0;
    virtual void UpdateProjection(glm::mat4 projection) = 0;
};