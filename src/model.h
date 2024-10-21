#pragma once

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>


class Model 
{
private:
    GLuint vbo;
    GLuint vao;
    size_t vertices_count;
public:
    Model(std::vector<float> vertices);
    Model(const float vertices[], size_t length);
    void SetModel();
    size_t GetVerticesCount();
    ~Model();
};