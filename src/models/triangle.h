#ifndef TRIANGLE
#define TRIANGLE

#include "model.h"


class Triangle : public Model
{
private:
    static GLuint default_vao;
    static GLuint GetDefaultVao();
public:
    void Draw(Shader *shader, glm::vec4 transformation) override;
    Triangle(Point point_a, Point point_b, Point point_c);
    Triangle(GLuint vao, Point point_a, Point point_b, Point point_c);
    static void DeleteDefaultVAO();
};

#endif