#include "textureManager.h"

std::string TextureManager::base_dir = "/home/mirotorch/vsb3r/zpg/cv2/textures/";

std::map<std::string, GLuint> TextureManager::texture_map;
std::mutex TextureManager::map_mutex;

void TextureManager::Clear()
{
    std::map<std::string, GLuint>::iterator it;
    for (it = texture_map.begin(); it != texture_map.end(); it++)
    {
        glDeleteTextures(1, &it->second);
    }
}

GLuint TextureManager::GetTextureId(std::string texture_name)
{
    std::lock_guard<std::mutex> guard(map_mutex);

    if (texture_map.find(texture_name) != texture_map.end())
    {
        return texture_map[texture_name];
    }
    else
    {
        GLuint texture = SOIL_load_OGL_texture((base_dir + texture_name).c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (texture == 0)
        {
            std::cerr << "texture load failed, path=" << base_dir + texture_name << std::endl;
            exit(1);
        }
        texture_map[texture_name] = texture;
        return texture;
    }
}
