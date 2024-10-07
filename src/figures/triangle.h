#ifndef TRIANGLE
#define TRIANGLE

#include "figure.h"


class Triangle : public Figure
{
private:
    static VertexArray* vao;
public:
    void Draw() override;
    Triangle(Point point_a, Point point_b, Point point_c);
    void DeleteVAO();
};

#endif