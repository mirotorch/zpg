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
    texture_unit = glGetUniformLocation(this->shader_program, "textureUnit");

    point_light_count = glGetUniformLocation(this->shader_program, "pointLightCount");
    dir_light_count = glGetUniformLocation(this->shader_program, "dirLightCount");
    UseProgram();
    glUniform1i(texture_unit, 0);
    glUniform1i(point_light_count, 0);
    glUniform1i(dir_light_count, 0);
    glUniform1i(spotlight_count, 0);
    glUseProgram(0);
}

ShaderProgram::ShaderProgram(GLuint id)
{
    this->shader_program = id;
    UseProgram();
    model_matrix = glGetUniformLocation(this->shader_program, "modelMatrix");
    projection_matrix = glGetUniformLocation(this->shader_program, "projectionMatrix");
    view_matrix = glGetUniformLocation(this->shader_program, "viewMatrix");
    camera_position = glGetUniformLocation(this->shader_program, "cameraPosition");
    texture_unit = glGetUniformLocation(this->shader_program, "textureUnit");

    point_light_count = glGetUniformLocation(this->shader_program, "pointLightCount");
    dir_light_count = glGetUniformLocation(this->shader_program, "dirLightCount");
    spotlight_count = glGetUniformLocation(this->shader_program, "spotlightCount");
    glUniform1i(texture_unit, 0);
    glUniform1i(point_light_count, 0);
    glUniform1i(dir_light_count, 0);
    glUniform1i(spotlight_count, 0);
    glUseProgram(0);
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


void ShaderProgram::UpdateView(glm::mat4 view, glm::vec3 center, glm::vec3 eye)
{
    this->UseProgram();
    glUniformMatrix4fv(view_matrix, 1, GL_FALSE, &view[0][0]);

    glUniform3f(camera_position, center[0], center[1], center[2]);
    
    for (int i = 0; i < flashlights.size(); i++) {
        glUniform3fv(glGetUniformLocation(shader_program,
            ("spotlights[" + std::to_string(flashlights.at(i)) + "].position").c_str()), 1, &eye[0]);
        glUniform3fv(glGetUniformLocation(shader_program,
            ("spotlights[" + std::to_string(flashlights.at(i)) + "].direction").c_str()), 1, &(glm::normalize(center))[0]);
    }

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

void ShaderProgram::SetTextureUnit(int unit)
{
    UseProgram();
    glUniform1i(texture_unit, unit);
    glUseProgram(0);
}

void ShaderProgram::AddLight(PointLight l)
{
    int count;
    glGetUniformiv(shader_program, point_light_count, &count);
    if (count >= MAX_POINT_LIGHTS) 
    {
        std::cout << "max point light reached" << std::endl;
        return;
    }
    UseProgram();
    count++;
    glUniform1i(point_light_count, count);
    UpdateLight(count - 1, l);
    glUseProgram(0);
}

void ShaderProgram::AddLight(DirLight l)
{
    int count;
    glGetUniformiv(shader_program, dir_light_count, &count);
    if (count >= MAX_DIR_LIGHTS) 
    {
        std::cout << "max dir light reached" << std::endl;
        return;
    }
    UseProgram();
    count++;
    glUniform1i(dir_light_count, count);
    UpdateLight(count - 1, l);
    glUseProgram(0);
}

void ShaderProgram::AddLight(Spotlight l)
{
    int count;
    glGetUniformiv(shader_program, spotlight_count, &count);
    if (count >= MAX_DIR_LIGHTS) 
    {
        std::cout << "max spotlight reached" << std::endl;
        return;
    }
    if (l.flashlight)
    {
        flashlights.push_back(count);
    }
    UseProgram();
    count++;
    glUniform1i(spotlight_count, count);
    UpdateLight(count - 1, l);
    glUseProgram(0);
}

void ShaderProgram::UpdateLight(int index, PointLight l)
{
    int count;
    glGetUniformiv(shader_program, point_light_count, &count);
    if (index >= count || index < 0) 
    {
        std::cerr << "UpdateLight(): invalid index " << index << ", point_light_count=" << count << std::endl;
        return;
    }
    
    std::string baseName = "pointLights[" + std::to_string(index) + "]";
    glUniform3fv(glGetUniformLocation(shader_program, (baseName + ".position").c_str()), 1, &l.position[0]);
    glUniform3fv(glGetUniformLocation(shader_program, (baseName + ".color").c_str()), 1, &l.color[0]);
    glUniform1f(glGetUniformLocation(shader_program, (baseName + ".constant").c_str()), l.constant);
    glUniform1f(glGetUniformLocation(shader_program, (baseName + ".linear").c_str()), l.linear);
    glUniform1f(glGetUniformLocation(shader_program, (baseName + ".quadratic").c_str()), l.quadratic);
}

void ShaderProgram::UpdateLight(int index, DirLight l)
{
    int count;
    glGetUniformiv(shader_program, dir_light_count, &count);
    if (index >= count || index < 0) 
    {
        std::cerr << "UpdateLight(): invalid index " << index << ", dir_light_count=" << count << std::endl;
        return;
    }
    std::string baseName = "dirLights[" + std::to_string(index) + "]";
    glUniform3fv(glGetUniformLocation(shader_program, (baseName + ".color").c_str()), 1, &l.color[0]);
    glUniform3fv(glGetUniformLocation(shader_program, (baseName + ".direction").c_str()), 1, &l.direction[0]);
}

void ShaderProgram::UpdateLight(int index, Spotlight l)
{
    int count;
    glGetUniformiv(shader_program, spotlight_count, &count);
    if (index >= count || index < 0) 
    {
        std::cerr << "UpdateLight(): invalid index " << index << ", spotlight_count=" << count << std::endl;
        return;
    }
    std::string baseName = "spotlights[" + std::to_string(index) + "]";
    glUniform3fv(glGetUniformLocation(shader_program, (baseName + ".position").c_str()), 1, &l.position[0]);
    glUniform3fv(glGetUniformLocation(shader_program, (baseName + ".direction").c_str()), 1, &l.direction[0]);
    glUniform3fv(glGetUniformLocation(shader_program, (baseName + ".color").c_str()), 1, &l.color[0]);
    glUniform1f(glGetUniformLocation(shader_program, (baseName + ".cutoff").c_str()), l.cutoff);
    glUniform1f(glGetUniformLocation(shader_program, (baseName + ".outerCutoff").c_str()), l.outerCutoff);
    glUniform1f(glGetUniformLocation(shader_program, (baseName + ".constant").c_str()), l.constant);
    glUniform1f(glGetUniformLocation(shader_program, (baseName + ".linear").c_str()), l.linear);
    glUniform1f(glGetUniformLocation(shader_program, (baseName + ".quadratic").c_str()), l.quadratic);
}