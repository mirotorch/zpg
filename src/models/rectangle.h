#ifndef RECTANGLE
#define RECTANGLE

#include "model.h"

class Rectangle : public Model
{
private:
    static VertexArray* vao;
public:
    void Draw(Shader *shader, glm::vec4 transformation) override;
    Rectangle(Point bottomLeft, Point topRight);
    void DeleteVAO();
};

#endif