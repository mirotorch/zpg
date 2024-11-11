#include "model.h"

Model::Model(const float vertices[], size_t array_length, size_t vertices_count) 
: Model(std::vector(vertices, vertices + array_length), vertices_count)
{    
}

Model::Model(std::vector<float> vertices, size_t vertices_count)
{
    this->vertices_count = vertices_count;

    glGenBuffers(1, &vbo); 
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW); 

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}


void Model::SetModel() 
{
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBindVertexArray(this->vao);
}

size_t Model::GetVerticesCount()
{
    return vertices_count;
}

Model::~Model()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}