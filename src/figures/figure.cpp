#include "figure.h"


float* ColoredPointArray(Point &point, Color &color)
{
    float* arr = new float[7] {point.x, point.y, point.z, color.x, color.y, color.z, color.w};
    return arr;
}

Figure::~Figure()
{
    delete vbo;
}