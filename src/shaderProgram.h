#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


// file IO
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class ShaderProgram
{
private:
    GLuint shader_program = 0;
    GLint model_matrix = 0;
    GLint view_matrix = 0;
    GLint position_matrix = 0;
    std::string ReadGlsl(const char* path);
    void CheckCompileStatus(const char* shader_path, GLuint id);
public:
    ShaderProgram(const char *vertex_path, const char *fragment_path);
    void UseProgram(); 
    void SetMatrixes(glm::mat4 model, glm::mat4 view, glm::mat4 position);
    ~ShaderProgram();
};

#endif