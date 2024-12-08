#pragma once


#include "movement.hpp"

class CubicBezierMovement : public Movement
{
private:
    glm::vec3 P0;
    glm::vec3 P1;
    glm::vec3 P2;
    glm::vec3 P3;
    float t;
    float speed;
public:
    CubicBezierMovement(glm::vec3 P0, glm::vec3 P1, glm::vec3 P2, glm::vec3 P3, float speed);
    std::unique_ptr<Transformation> GetNextPosition();
};