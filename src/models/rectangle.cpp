#include "rectangle.h"

VertexArray* Rectangle::vao = nullptr;


void Rectangle::Draw(Shader *shader, glm::vec4 transformation)
{
    if (!shader)
    {
        fputs("Rectangle: shader not found", stderr);
        throw std::runtime_error("shader not found");
    }
    vbo->Bind();
    vao->Bind();
    shader->UseProgram();

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

Rectangle::Rectangle(Point bottomLeft, Point topRight)
{
    float data[] = {
        bottomLeft.x, bottomLeft.y, bottomLeft.z,
        topRight.x, bottomLeft.y, bottomLeft.z,
        bottomLeft.x, topRight.y, bottomLeft.z,

        topRight.x, bottomLeft.y, bottomLeft.z,
        topRight.x, topRight.y, bottomLeft.z,
        bottomLeft.x, topRight.y, bottomLeft.z
    };
    vbo = new VertexBuffer(data, sizeof(data));
    vbo->Bind();
    if (!vao)
    {
        vao = new VertexArray();
        vao->Bind();
        vao->AddAttribute(3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid *)0);
    }
}

void Rectangle::DeleteVAO()
{
    if (vao) delete vao;
}
