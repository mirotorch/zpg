#pragma once

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

#include <vector>
#include <iostream>

class Model 
{
private:
    const char* model_path = "models/";
    GLuint vbo;
    GLuint ibo = 0;
    GLuint vao;
    size_t vertices_count;

    struct Vertex
    {
    float Position[3];
    float Normal[3];
    float Texture[2];
    float Tangent[3];
    };
public:
    Model(std::vector<float> vertices, size_t vertices_count, bool textured = false);
    Model(const float vertices[], size_t array_length, size_t vertices_count, bool textured = false);
    Model(std::string model_name);
    void SetModel();
    size_t GetVerticesCount();
    bool HasIbo();
    ~Model();
};