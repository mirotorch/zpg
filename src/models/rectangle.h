#ifndef RECTANGLE
#define RECTANGLE

#include "model.h"

class Rectangle : public Model
{
public:
    Rectangle(Point bottomLeft, Point topRight);
};

#endif