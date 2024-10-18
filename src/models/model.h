#ifndef MODEL
#define MODEL

#include "../shaderProgram.h"      
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

typedef glm::vec3 Point;
typedef glm::vec4 Color;

float* ColoredPointArray(Point &point, Color &color);

class Model {
public:
    ~Model();
protected:
    GLuint vbo;
    GLuint vao;
    int triangle_count;
public:
    void BindVBO();
    void BindVAO();
    int GetTriangleCount();
};

#endif