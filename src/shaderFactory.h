#ifndef SHADER_FACTORY
#define SHADER_FACTORY

#include "shaderProgram.h"
#include <iostream>
#include <map>
#include <mutex>

class ShaderFactory 
{
private:
    std::string shader_dir;
    std::map<std::string, ShaderProgram*> shader_map;
    std::mutex map_mutex;
public:
    ShaderFactory(std::string shader_dir);
    ~ShaderFactory();

    ShaderProgram* GetShader(std::string vertex_name, std::string fragment_name);
};

#endif