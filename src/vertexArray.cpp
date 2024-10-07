#include "vertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &this->id);
    glBindVertexArray(this->id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &this->id);
}

int VertexArray::GetAttributeCount()
{
    return this->attrib_count;
}

void VertexArray::AddAttribute(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer)
{
    glEnableVertexAttribArray(this->attrib_count);
    glVertexAttribPointer(this->attrib_count++, size, type, normalized, stride, pointer);
}

void VertexArray::Bind()
{
    GLuint current_VAO;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, reinterpret_cast<GLint*>(&current_VAO));
    if (current_VAO != this->id)
        glBindVertexArray(this->id);
}