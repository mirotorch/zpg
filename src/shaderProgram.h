#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "ICameraObserver.hpp"

// file IO
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class ShaderProgram : public ICameraObserver
{
private:
    GLuint shader_program = 0;
    GLint model_matrix = 0;
    GLint view_matrix = 0;
    GLint projection_matrix = 0;
    std::string ReadGlsl(const char* path);
    void CheckCompileStatus(const char* shader_path, GLuint id);
public:
    ShaderProgram(const char *vertex_path, const char *fragment_path);
    void UseProgram(); 
    void UpdateModel(glm::mat4 model);
    virtual void UpdateView(glm::mat4 view);
    virtual void UpdateProjection(glm::mat4 projection);
    ~ShaderProgram();
};  

#endif