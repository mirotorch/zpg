#include "shader.h"

std::string Shader::ReadGlsl(const char *path)
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

Shader::Shader(const char *vertex_path, const char *fragment_path)
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

    model_transform = glGetUniformLocation(this->shader_program, "modelMatrix");
}

void Shader::UseProgram(glm::mat4 transformation)
{
    // GLint current_program;
    // glGetIntegerv(GL_CURRENT_PROGRAM, &current_program);
    // if (current_program != this->shader_program)
    // {
        glUseProgram(this->shader_program);
        glUniformMatrix4fv(model_transform, 1, GL_FALSE, &transformation[0][0]);
    // }
}

void Shader::CheckCompileStatus(const char* shader_path, GLuint id)
{
    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == 0)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "Shader compilation failure\n"
                  << infoLog << std::endl << shader_path << std::endl;
        throw std::runtime_error("Shader compilation failure");
    }
}

Shader::~Shader()
{
    glDeleteProgram(this->shader_program);
}
