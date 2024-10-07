#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexBuffer {
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    void Bind();
private:
    GLuint id; 
};


#endif 