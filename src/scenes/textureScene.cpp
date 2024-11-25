#include "textureScene.h"
#include "../models/textured.h"


TextureScene::TextureScene(std::string shader_path, GLFWwindow *window)
    : Scene(shader_path, window)
{
    SetupCamera(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    LoadTextures(std::vector<std::string> {"wooden_fence.png"});
}

void TextureScene::CreateDrawableObjects()
{
    std::vector<float> textured_vertices(textured, textured + sizeof(textured) / sizeof(float));
    Model* m = new Model(textured_vertices, textured_vertices.size(), true);
    Material mat;
    mat.ambient = glm::vec3(0.1f);
    mat.diffuse = glm::vec3(1.0f);
    mat.specular = glm::vec3(0.5f);
    mat.shininess = 32;
    DrawableObject* dwo = new DrawableObject();
    dwo->model = m;
    dwo->material = mat;
    dwo->shader = shader_factory->GetShader("phong_v", "phong_textured_f");
    dwo->transformation = new CompoundTransformation();
    dwo->texture_unit = 0;
    drawable_objects.push_back(dwo);


    DirLight dl;
    dl.color = glm::vec3(1.0f);
    dl.direction = glm::vec3(0.0f, 0.0f, 1.0f);
    shader_factory->GetShader("phong_v", "phong_textured_f")->AddLight(dl);
}
