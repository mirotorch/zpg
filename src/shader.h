#ifndef SHADER
#define SHADER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>


// file IO
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
private:
    GLuint shader_program = 0;
    GLint model_transform = 0;
    std::string ReadGlsl(const char* path);
    void CheckCompileStatus(const char* shader_path, GLuint id);
public:
    Shader(const char *vertex_path, const char *fragment_path);
    void UseProgram(glm::mat4 M); 
    ~Shader();
};

#endif