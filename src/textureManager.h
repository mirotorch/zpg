#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <soil2/SOIL2.h>

#include <map>
#include <mutex>
#include <vector>
#include <iostream>

class TextureManager
{
    static std::map<std::string, GLuint> texture_map;
    static std::string base_dir;
    static std::mutex map_mutex;
    const char* uniform_texture_unit = "textureUnit";
public:
    static void Clear();
    static GLuint GetTextureId(std::string texture_name);
};