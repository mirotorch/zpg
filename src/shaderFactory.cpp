#include "shaderFactory.h"

ShaderFactory::ShaderFactory(std::string shader_dir, Camera* camera)
{
    this->shader_dir = shader_dir;
    this->camera = camera;
}

ShaderFactory::~ShaderFactory()
{
    std::map<std::string, ShaderProgram*>::iterator it;
    for (it = shader_map.begin(); it != shader_map.end(); it++)
    {
        delete it->second;  
    }
}

ShaderProgram* ShaderFactory::GetShader(std::string vertex_name, std::string fragment_name)
{
    std::string key_string = vertex_name + ";" + fragment_name;
    
    std::lock_guard<std::mutex> guard(map_mutex);

    if (shader_map.find(key_string) != shader_map.end())
    {
        return shader_map[key_string];
    }
    else
    {
        std::string vertex_path = shader_dir + vertex_name + ".glsl";
        std::string fragment_path = shader_dir + fragment_name + ".glsl";
        ShaderProgram* shader = new ShaderProgram(vertex_path.c_str(), fragment_path.c_str());
        shader_map[key_string] = shader;
        camera->Subscribe(shader);
        return shader;
    }
}