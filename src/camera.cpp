#include "camera.h"
#include "stdio.h"

void Camera::NotifyViewChanged()
{
    printf("eye: %f, %f, %f\n", eye.x, eye.y, eye.z);
    printf("center: %f, %f, %f\n", center.x, center.y, center.z);
    printf("up: %f %f %f\n", up.x, up.y, up.z);
    printf("--------------------\n");
    glm::mat4 view = glm::lookAt(eye, center + eye, up);
    for (auto observer : observers)
    {
        observer->UpdateView(view, center, eye);
    }
}

void Camera::NotifyProjectionChanged()
{
    for (auto observer : observers)
    {
        observer->UpdateProjectionMatrix(projection);
    }
}

Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    this->eye = eye;
    this->center = center;
    this->up = up;
    projection = glm::mat4(1.0f);
    yaw = 0;
    pitch = 0;
}

void Camera::UpdateVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    center = glm::normalize(front);

    // up = glm::normalize(glm::cross(glm::cross(front, up), front));
    NotifyViewChanged();
}

void Camera::Rotate(float deltaYaw, float deltaPitch)
{
    yaw += deltaYaw;
    pitch += deltaPitch;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    UpdateVectors();
}

void Camera::Subscribe(ICameraObserver *listener)
{
    observers.insert(listener);
    listener->UpdateView(glm::lookAt(eye, center, up), center, eye);
    listener->UpdateProjectionMatrix(projection);
}

void Camera::Unsubscribe(ICameraObserver *listener)
{
    observers.erase(listener);
}

void Camera::SetupProjectionPerspective(float aspect, float zNear, float zFar)
{
    this->projection_type = PERSPECTIVE;
    this->projection = glm::perspective(fov, aspect, zNear, zFar);
    NotifyProjectionChanged();
}

void Camera::SetupProjectionOrthogonal(float left, float right, float bottom, float top, float zNear, float zFar)
{
    this->projection_type = ORTHOGONAL;
    this->projection = glm::ortho(left, right, bottom, top, zNear, zFar);
    NotifyProjectionChanged();
}

void Camera::ToRight()
{
    eye += glm::normalize(glm::cross(center, up));
    NotifyViewChanged();
}

void Camera::ToLeft()
{
    eye -= glm::normalize(glm::cross(center, up));
    NotifyViewChanged();
}

void Camera::ToFront()
{
    eye += glm::normalize(center);
    NotifyViewChanged();
}

void Camera::ToBack()
{
    eye -= glm::normalize(center);
    NotifyViewChanged();
}