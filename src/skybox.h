#pragma once

#include <soil2/SOIL2.h>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderLoader.h"
#include "ICameraObserver.hpp"
#include "camera.h"

class Skybox : public ICameraObserver
{
    GLuint vbo;
    GLuint vao;
    GLuint shader_program;
    GLuint texture;
public:
    GLuint texture_unit = -1;
    Skybox(Camera* camera, glm::vec3 scale);
    ~Skybox();
    void Draw();

    void UpdateViewMatrix(glm::mat4 view);
    void UpdateCameraPosition(glm::vec3 view);
    void UpdateProjectionMatrix(glm::mat4 projection);
};