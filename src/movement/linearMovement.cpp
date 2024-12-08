#include "linearMovement.h"

LinearMovement::LinearMovement(glm::vec3 start_point, glm::vec3 end_point, float speed)
{
    this->speed = speed;
    this->A = start_point;
    this->B = end_point;
    this->t = 0;
}

std::unique_ptr<Transformation> LinearMovement::GetNextPosition()
{
    std::unique_ptr<Transformation> point = std::make_unique<Translation>(Translation(A + t * (B - A)));
    t += speed;
    if (t > 1)
    {
        t = 0;
        std::swap(A, B);
    }
    return std::move(point);
}