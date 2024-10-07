#ifndef RECTANGLE
#define RECTANGLE

#include "figure.h"

class Rectangle : public Figure
{
private:
    static VertexArray* vao;
public:
    void Draw() override;
    Rectangle(Point bottomLeft, Point topRight);
    void DeleteVAO();
};

#endif