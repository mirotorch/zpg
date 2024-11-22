#include "shaderProgram.h"


std::string ShaderProgram::ReadGlsl(const char *path)
{
    std::ifstream shader_file;
    std::stringstream shader_stream;

    try
    {
        shader_file.open(path);
        shader_stream << shader_file.rdbuf();
        shader_file.close();
        return shader_stream.str();
    }
    catch (std::ifstream::failure &e)
    {
        std::cerr << "Failed to read shader file: " << e.what() << std::endl;
        return "";
    }
}

ShaderProgram::ShaderProgram(const char *vertex_path, const char *fragment_path)
{
    std::string vertex_str = ReadGlsl(vertex_path);
    std::string fragment_str = ReadGlsl(fragment_path);
    const char *vertex_code = vertex_str.c_str();
    const char *fragment_code = fragment_str.c_str();

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_code, NULL);
    glCompileShader(vertex_shader);
    CheckCompileStatus(vertex_path, vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_code, NULL);
    glCompileShader(fragment_shader);
    CheckCompileStatus(fragment_path, fragment_shader);

    this->shader_program = glCreateProgram();
    glAttachShader(shader_program, fragment_shader);
    glAttachShader(shader_program, vertex_shader);
    glLinkProgram(shader_program);

    GLint status;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shader_program, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
        throw std::runtime_error("Linker failure");
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    model_matrix = glGetUniformLocation(this->shader_program, "modelMatrix");
    projection_matrix = glGetUniformLocation(this->shader_program, "projectionMatrix");
    view_matrix = glGetUniformLocation(this->shader_program, "viewMatrix");
    camera_position = glGetUniformLocation(this->shader_program, "cameraPosition");

    lights = glGetUniformLocation(this->shader_program, "lights");
    light_count = glGetUniformLocation(this->shader_program, "lightCount");
}

ShaderProgram::ShaderProgram(GLuint id)
{
    this->shader_program = id;
    model_matrix = glGetUniformLocation(this->shader_program, "modelMatrix");
    projection_matrix = glGetUniformLocation(this->shader_program, "projectionMatrix");
    view_matrix = glGetUniformLocation(this->shader_program, "viewMatrix");
    camera_position = glGetUniformLocation(this->shader_program, "cameraPosition");

    lights = glGetUniformLocation(this->shader_program, "lights");
    light_count = glGetUniformLocation(this->shader_program, "lightCount");
}

void ShaderProgram::UseProgram()
{
    GLint current_program;
    glGetIntegerv(GL_CURRENT_PROGRAM, &current_program);
    if (current_program != this->shader_program)
    {
        glUseProgram(this->shader_program);
    }
}

void ShaderProgram::UpdateModel(glm::mat4 model)
{
    UseProgram();
    glUniformMatrix4fv(model_matrix, 1, GL_FALSE, &model[0][0]);
    glUseProgram(0);
}


void ShaderProgram::UpdateViewMatrix(glm::mat4 view)
{
    this->UseProgram();
    glUniformMatrix4fv(view_matrix, 1, GL_FALSE, &view[0][0]);
    glUseProgram(0);
}

void ShaderProgram::UpdateProjectionMatrix(glm::mat4 projection)
{
    this->UseProgram();
    glUniformMatrix4fv(projection_matrix, 1, GL_FALSE, &projection[0][0]);
    glUseProgram(0);
}

void ShaderProgram::CheckCompileStatus(const char *shader_path, GLuint id)
{
    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == 0)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "Shader compilation failure\n"
                  << infoLog << std::endl
                  << shader_path << std::endl;
        throw std::runtime_error("Shader compilation failure");
    }
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(this->shader_program);
}

void ShaderProgram::SetMaterial(Material m)
{
    UseProgram();
    std::string base_name = "material";
    glUniform3fv(glGetUniformLocation(shader_program, (base_name + ".ambient").c_str()), 1, &m.ambient[0]);
    glUniform3fv(glGetUniformLocation(shader_program, (base_name + ".diffuse").c_str()), 1, &m.diffuse[0]);
    glUniform3fv(glGetUniformLocation(shader_program, (base_name + ".specular").c_str()), 1, &m.specular[0]);
    glUniform1f(glGetUniformLocation(shader_program, (base_name + ".shininess").c_str()), m.shininess);
    glUseProgram(0);
}

void ShaderProgram::UpdateCameraPosition(glm::vec3 view)
{
    this->UseProgram();
    glUniform3f(camera_position, view[0], view[1], view[2]);
    glUseProgram(0);
}

void ShaderProgram::AddLight(Light l)
{
    if (light_count_local >= MAX_LIGHTS) 
    {
        std::cout << "max light reached" << std::endl;
        return;
    }
    UseProgram();
    std::string base_name = "lights[" + std::to_string(light_count_local) + "]";
    glUniform3fv(glGetUniformLocation(shader_program, (base_name + ".position").c_str()), 1, &l.position[0]);
    glUniform3fv(glGetUniformLocation(shader_program, (base_name + ".color").c_str()), 1, &l.color[0]);
    glUniform1f(glGetUniformLocation(shader_program, (base_name + ".constant").c_str()), l.constant);
    glUniform1f(glGetUniformLocation(shader_program, (base_name + ".linear").c_str()), l.linear);
    glUniform1f(glGetUniformLocation(shader_program, (base_name + ".quadratic").c_str()), l.quadratic);
    light_count_local++;
    glUniform1i(light_count, light_count_local);
    glUseProgram(0);
}

void ShaderProgram::UpdateLight(int index, Light l)
{

    if (index >= light_count_local || index < 0) 
    {
        std::cerr << "UpdateLight(): invalid index " << index << ", light_count=" << light_count_local << std::endl;
        return;
    }
    
    std::string baseName = "lights[" + std::to_string(light_count_local) + "]";
    glUniform3fv(glGetUniformLocation(shader_program, (baseName + ".position").c_str()), 1, &l.position[0]);
    glUniform3fv(glGetUniformLocation(shader_program, (baseName + ".color").c_str()), 1, &l.color[0]);
    glUniform1f(glGetUniformLocation(shader_program, (baseName + ".constant").c_str()), l.constant);
    glUniform1f(glGetUniformLocation(shader_program, (baseName + ".linear").c_str()), l.linear);
    glUniform1f(glGetUniformLocation(shader_program, (baseName + ".quadratic").c_str()), l.quadratic);
}
