#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "ICameraObserver.hpp"
#include "light.hpp"
#include "material.hpp"

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
    GLint camera_position = 0;
    GLint texture_unit = 0;

    GLint point_light_count = 0;
    GLint dir_light_count = 0;
    GLint spotlight_count = 0;

    std::string ReadGlsl(const char* path);
    void CheckCompileStatus(const char* shader_path, GLuint id);
public:
    ShaderProgram(const char *vertex_path, const char *fragment_path);
    ShaderProgram(GLuint id);

    void UseProgram(); 
    void UpdateModel(glm::mat4 model);

    // ICameraObserver
    void UpdateProjectionMatrix(glm::mat4 projection);
    void UpdateView(glm::mat4 view, glm::vec3 center, glm::vec3 eye);

    void AddLight(PointLight l);
    void AddLight(DirLight l);
    void AddLight(Spotlight l);
    void UpdateLight(int index, PointLight l);
    void UpdateLight(int index, DirLight l);
    void UpdateLight(int index, Spotlight l);
    void SetMaterial(Material m);
    void SetTextureUnit(int unit);

    ~ShaderProgram();
};  

#endif