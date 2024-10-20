#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ICameraObserver.hpp"
#include <set>

class ShaderProgram;

enum ProjectionType 
{
    PERSPECTIVE = 0,
    ORTHOGONAL = 1
};

class Camera
{
  private:
    const float fov = glm::radians(45.0f);
    float yaw;
    float pitch;
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
    glm::mat4 projection;
    ProjectionType projection_type;
    std::set<ICameraObserver*> observers;
    void NotifyViewChanged();
    void NotifyProjectionChanged();
    void UpdateVectors();
  public:
    Camera();
    void Rotate(float deltaYaw, float deltaPitch); 

    void Subscribe(ICameraObserver* listener);
    void Unsubscribe(ICameraObserver* listener);

    void SetupProjectionPerspective(float aspect, float zNear, float zFar);
    void SetupProjectionOrthogonal(float left, float right, float botton, float top, float zNear, float zFar);

    void ToRight();
    void ToLeft();
    void ToFront();
    void ToBack();
};