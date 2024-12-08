#pragma once


#include "movement.hpp"

class LinearMovement : public Movement
{
private:
    float t;
    float speed;
    glm::vec3 A;
    glm::vec3 B;
public:
    LinearMovement(glm::vec3 start_point, glm::vec3 end_point, float speed);
    std::unique_ptr<Transformation> GetNextPosition();
};