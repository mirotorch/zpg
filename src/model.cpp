#include "model.h"
#include "models/tree.h"

Model::Model(const float vertices[], size_t length) : Model(std::vector(vertices, vertices + length))
{    
}

Model::Model(std::vector<float> vertices)
{
    this->vertices_count = sizeof(tree) / sizeof(float);//vertices.size();

    glGenBuffers(1, &vbo); 
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tree), tree, GL_STATIC_DRAW); 

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