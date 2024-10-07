#ifndef RECTANGLE
#define RECTANGLE

#include "model.h"

class Rectangle : public Model
{
private:
    static GLuint default_vao;
    static GLuint GetDefaultVao();
public:
    void Draw(Shader *shader, glm::vec4 transformation) override;
    Rectangle(Point bottomLeft, Point topRight);
    Rectangle(GLuint vao, Point bottomLeft, Point topRight);
    static void DeleteDefaultVAO();
};

#endif