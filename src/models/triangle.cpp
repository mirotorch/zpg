#include "triangle.h"

VertexArray* Triangle::vao = nullptr;

void Triangle::Draw(Shader* shader, glm::vec4 transformation)
{
    if (!shader)
    {
        fputs("Triangle: shader not found", stderr);
        throw std::runtime_error("shader not found");
    }
    vbo->Bind();
    vao->Bind();
    shader->UseProgram();

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

Triangle::Triangle(Point point_a, Point point_b, Point point_c)
{
    float data[9] = 
    {
        point_a.x, point_a.y, point_a.z,
        point_b.x, point_b.y, point_b.z,
        point_c.x, point_c.y, point_c.z
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

void Triangle::DeleteVAO()
{
    if (vao) delete vao;
}