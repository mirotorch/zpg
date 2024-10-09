#ifndef MODEL
#define MODEL

#include "../shader.h"      
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

typedef glm::vec3 Point;
typedef glm::vec4 Color;

float* ColoredPointArray(Point &point, Color &color);

class Model {
public:
    virtual void Draw(Shader *shader, glm::vec4 transformation) = 0;
    ~Model();
protected:
    // Model(const void* data, int size);
    GLuint vbo;
    GLuint vao;
    void BindVBO();
    void BindVAO();
};

#endif