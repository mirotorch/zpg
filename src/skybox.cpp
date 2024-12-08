#include "skybox.h"
#include "models/skycube.h"
#include "textureManager.h"

Skybox::Skybox(Camera* camera, glm::vec3 scale)
{

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float), skycube, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    ShaderLoader* sl = new ShaderLoader();
    this->shader_program = sl->loadShader("/home/mirotorch/vsb3r/zpg/cv2/shaders/skybox_v.glsl", 
        "/home/mirotorch/vsb3r/zpg/cv2/shaders/skybox_f.glsl");
    delete sl;


    std::string path = "/home/mirotorch/vsb3r/zpg/cv2/textures/sky/cubemap/";
    this->texture = SOIL_load_OGL_cubemap(
        (path + "posx.jpg").c_str(), (path + "negx.jpg").c_str(), 
        (path + "posy.jpg").c_str(), (path + "negy.jpg").c_str(), 
        (path + "posz.jpg").c_str(), (path + "negz.jpg").c_str(), 
        SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS
    );

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    glm::mat4 model_matrix(1.0f);
    glUseProgram(this->shader_program);
    glUniformMatrix4fv(glGetUniformLocation(this->shader_program, "modelMatrix"), 1, GL_FALSE, 
        &glm::scale(model_matrix, scale)[0][0]);
    glUseProgram(0);

    camera->Subscribe(this);
}

Skybox::~Skybox()
{
    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Skybox::Draw()
{
    glDepthMask(GL_FALSE);
    glBindVertexArray(this->vao);
    glUseProgram(this->shader_program);
    glDrawArrays(GL_TRIANGLES, 0, 108);
    glUseProgram(0);
    glDepthMask(GL_TRUE);
}

void Skybox::UpdateViewMatrix(glm::mat4 view)
{
    glUseProgram(this->shader_program);
    glUniformMatrix4fv(glGetUniformLocation(this->shader_program, "viewMatrix"), 1, GL_FALSE, &view[0][0]);
    glUseProgram(0);
}

void Skybox::UpdateCameraPosition(glm::vec3 view)
{
    glUseProgram(this->shader_program);
    glUniform3fv(glGetUniformLocation(this->shader_program, "cameraPosition"), 1, &view[0]);
    glUseProgram(0);
}

void Skybox::UpdateProjectionMatrix(glm::mat4 projection)
{
    glUseProgram(this->shader_program);
    glUniformMatrix4fv(glGetUniformLocation(this->shader_program, "projectionMatrix"), 1, GL_FALSE, &projection[0][0]);
    glUseProgram(0);
}
