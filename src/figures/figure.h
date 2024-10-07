#ifndef FIGURE
#define FIGURE

#include "../vertexArray.h"
#include "../shader.h"      
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

typedef glm::vec3 Point;
typedef glm::vec4 Color;

float* ColoredPointArray(Point &point, Color &color);

class Figure {
public:
    virtual void Draw() = 0;
    ~Figure();
    Shader* shaders;
protected:
    VertexBuffer* vbo;
};

#endif