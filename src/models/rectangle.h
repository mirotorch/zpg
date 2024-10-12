#ifndef RECTANGLE
#define RECTANGLE

#include "model.h"

class Rectangle : public Model
{
public:
    void Draw(Shader *shader, glm::mat4 transformation) override;
    Rectangle(Point bottomLeft, Point topRight);
};

#endif