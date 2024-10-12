#include "triangle.h"

void Triangle::Draw(Shader* shader, glm::vec4 transformation)
{
    Model::Draw(shader, transformation);
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
    glGenBuffers(1, &this->vbo); 
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, data, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid *)0);
}