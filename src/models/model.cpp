#include "model.h"


float* ColoredPointArray(Point &point, Color &color)
{
    float* arr = new float[7] {point.x, point.y, point.z, color.x, color.y, color.z, color.w};
    return arr;
}


void Model::BindVAO()
{
    // GLuint current_VAO;
    // glGetIntegerv(GL_VERTEX_ARRAY_BINDING, reinterpret_cast<GLint*>(&current_VAO));
    // if (current_VAO != this->vao)
        glBindVertexArray(this->vao);
}

int Model::GetTriangleCount()
{
    return triangle_count;
}

Model::~Model()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Model::BindVBO()
{
    // GLuint current_VBO;
    // glGetIntegerv(GL_BUFFER_BINDING, reinterpret_cast<GLint*>(&current_VBO));
    // if (current_VBO != this->vbo)
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}