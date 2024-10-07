#include "rectangle.h"

GLuint Rectangle::GetDefaultVao()
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

GLuint Rectangle::default_vao = 0;


void Rectangle::Draw(Shader *shader, glm::vec4 transformation)
{
    if (!shader)
    {
        fputs("Rectangle: shader not found", stderr);
        throw std::runtime_error("shader not found");
    }
    shader->UseProgram();
    BindVAO();
    BindVBO();

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

Rectangle::Rectangle(Point bottomLeft, Point topRight) 
: Rectangle(Rectangle::GetDefaultVao(), bottomLeft, topRight)
{

}

Rectangle::Rectangle(GLuint vao, Point bottomLeft, Point topRight) : Model(0, vao)
{
    float data[] = {
        bottomLeft.x, bottomLeft.y, bottomLeft.z,
        topRight.x, bottomLeft.y, bottomLeft.z,
        bottomLeft.x, topRight.y, bottomLeft.z,

        topRight.x, bottomLeft.y, bottomLeft.z,
        topRight.x, topRight.y, bottomLeft.z,
        bottomLeft.x, topRight.y, bottomLeft.z
    };

    glGenBuffers(1, &this->vbo); 
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}

void Rectangle::DeleteDefaultVAO()
{
    glDeleteVertexArrays(1, &Rectangle::default_vao);
}