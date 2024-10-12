#include "rectangle.h"


void Rectangle::Draw(Shader *shader, glm::mat4 transformation)
{
    Model::Draw(shader, transformation);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

Rectangle::Rectangle(Point bottomLeft, Point topRight)
{
    float data[18] = {
        bottomLeft.x, bottomLeft.y, bottomLeft.z,
        topRight.x, bottomLeft.y, bottomLeft.z,
        bottomLeft.x, topRight.y, bottomLeft.z,

        topRight.x, bottomLeft.y, bottomLeft.z,
        topRight.x, topRight.y, bottomLeft.z,
        bottomLeft.x, topRight.y, bottomLeft.z
    };

    glGenBuffers(1, &this->vbo); 
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, data, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid *)0);
}