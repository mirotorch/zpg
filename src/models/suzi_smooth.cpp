#include "suzi_smooth.h"



void SuziSmooth::Draw(Shader * shader, glm::vec4 transformation)
{
    Model::Draw(shader, transformation);
    glDrawArrays(GL_TRIANGLES, 0, 17424);
}

SuziSmooth::SuziSmooth()
{
    glGenBuffers(1, &this->vbo); 
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 17424, suziSmooth, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}
