#include "shadingTestScene.h"
#include "../models/sphere.h"

void ShadingTestScene::CreateDrawableObjects()
{
    std::vector<float> sphere_vertices(sphere, sphere + sizeof(sphere) / sizeof(float));

    DrawableObject* dwo = new DrawableObject();
    dwo->model = new Model(sphere_vertices, 2880);
    dwo->transformation = new CompoundTransformation();
    dwo->shader = shader_factory->GetShader(shader_type == "lambert_f" ? "lambert_v" : "phong_v", shader_type);
    drawable_objects.push_back(dwo);
}


ShadingTestScene::ShadingTestScene(std::string shader_path, GLFWwindow* window, std::string shader_type)
: Scene(shader_path, window)
{
    this->shader_type = shader_type;
    SetupCamera(glm::vec3(0.0f, 0.0f, -4.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
