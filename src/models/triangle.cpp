#include "triangle.h"


GLuint Triangle::GetDefaultVao()
{
    if (default_vao != 0) return default_vao;
    GLuint id = 0;
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid *)0);
    default_vao = id;
    return id;
}

GLuint Triangle::default_vao = 0;

void Triangle::Draw(Shader* shader, glm::vec4 transformation)
{
    if (!shader)
    {
        fputs("Triangle: shader not found", stderr);
        throw std::runtime_error("shader not found");
    }
    shader->UseProgram();

    BindVAO();
    BindVBO();
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

Triangle::Triangle(Point point_a, Point point_b, Point point_c) 
: Triangle(Triangle::GetDefaultVao(), point_a, point_b, point_c)
{
}

Triangle::Triangle(GLuint vao, Point point_a, Point point_b, Point point_c) : Model(0, vao)
{
    float data[9] = 
    {
        point_a.x, point_a.y, point_a.z,
        point_b.x, point_b.y, point_b.z,
        point_c.x, point_c.y, point_c.z
    };
    glGenBuffers(1, &this->vbo); 
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}

void Triangle::DeleteDefaultVAO()
{
    glDeleteVertexArrays(1, &Triangle::default_vao);
}