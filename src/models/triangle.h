#ifndef TRIANGLE
#define TRIANGLE

#include "model.h"


class Triangle : public Model
{
public:
    void Draw(Shader *shader, glm::mat4 transformation) override;
    Triangle(Point point_a, Point point_b, Point point_c);
    Triangle(float pos_normale[18]);
};

#endif