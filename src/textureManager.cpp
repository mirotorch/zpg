#include "textureManager.h"

std::string TextureManager::base_dir = "/textures";

std::map<std::string, int> TextureManager::index_map;
std::vector<GLuint> TextureManager::textures;
std::mutex TextureManager::map_mutex;

void TextureManager::Clear()
{
    glDeleteTextures(textures.size(), &textures[0]);
}

int TextureManager::GetTextureUnit(std::string texture_name)
{
    std::lock_guard<std::mutex> guard(map_mutex);

    if (index_map.find(texture_name) != index_map.end())
    {
        return index_map[texture_name];
    }
    else
    {
        GLuint texture = SOIL_load_OGL_texture((base_dir + texture_name).c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (texture == 0)
        {
            std::cerr << "texture load failed, path=" << base_dir + texture_name << std::endl;
            exit(1);
        }
        int unit = textures.size();
        if (unit > 31) 
        {
            std::cerr << "too many textures" << std::endl;
            exit(1);
        }
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, texture);
        textures.push_back(texture);
        index_map[texture_name] = unit;
        return unit;
    }
}
