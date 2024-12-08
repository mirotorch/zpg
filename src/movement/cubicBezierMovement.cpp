#include "cubicBezierMovement.h"

CubicBezierMovement::CubicBezierMovement(glm::vec3 P0, glm::vec3 P1, glm::vec3 P2, glm::vec3 P3, float speed)
{
    this->t = 0;
    this->P0 = P0;
    this->P1 = P1;
    this->P2 = P2;
    this->P3 = P3;
    this->speed = speed;
}

std::unique_ptr<Transformation> CubicBezierMovement::GetNextPosition()
{
    float u = 1.0f - t; 
    float u2 = u * u;
    float u3 = u2 * u;
    float t2 = t * t;
    float t3 = t2 * t;
    glm::vec3 point = u3 * P0 + 3 * u2 * t * P1 + 3 * u * t2 * P2 + t3 * P3;
    t += speed;
    if (t > 1)
    {
        t = 0;
        std::swap(P0, P3);
        std::swap(P1, P2);
    }
    return std::move(std::make_unique<Translation>(Translation(point)));
}