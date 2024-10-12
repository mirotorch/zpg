#include "sphere.h"

void Sphere::Draw(Shader *shader, glm::mat4 transformation)
{
    Model::Draw(shader, transformation);
    glDrawArrays(GL_TRIANGLES, 0, 17280);
}

Sphere::Sphere()
{
    glGenBuffers(1, &this->vbo); 
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 17280, sphere, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}