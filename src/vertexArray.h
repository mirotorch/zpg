#ifndef VERTEX_ARRAY
#define VERTEX_ARRAY

#include "vertexBuffer.h"


class VertexArray
{
private:
    GLuint id;
    int attrib_count = 0;
public:
    VertexArray();
    ~VertexArray();
    int GetAttributeCount();
    void AddAttribute(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
    void Bind();
};


#endif  