#include "vertexBuffer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    glGenBuffers(1, &this->id); 
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &this->id);
}

void VertexBuffer::Bind()
{
    GLuint current_VBO;
    glGetIntegerv(GL_BUFFER_BINDING, reinterpret_cast<GLint*>(&current_VBO));
    if (current_VBO != this->id)
        glBindBuffer(GL_ARRAY_BUFFER, this->id);
}