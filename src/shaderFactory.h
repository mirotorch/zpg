#ifndef SHADER_FACTORY
#define SHADER_FACTORY

#include "shader.h"
#include <iostream>
#include <map>
#include <mutex>

class ShaderFactory 
{
private:
    std::string shader_dir;
    std::map<std::string, Shader*> shader_map;
    std::mutex map_mutex;
public:
    ShaderFactory(std::string shader_dir);
    ~ShaderFactory();

    Shader* GetShader(std::string vertex_name, std::string fragment_name);
};

#endif