#include "shadingTestScene.h"
#include "../models/sphere.h"

void ShadingTestScene::UpdateTransformations()
{
}

void ShadingTestScene::CreateDrawableObjects()
{
    std::vector<float> sphere_vertices(sphere, sphere + sizeof(sphere) / sizeof(float));

    DrawableObject* dwo = new DrawableObject();
    dwo->model = new Model(sphere_vertices, 2880);
    dwo->transformation = new CompoundTransformation();
    dwo->shader = shader_factory->GetShader(shader_type == "lambert_f" ? "lambert_v" : "phong_v", shader_type);
    drawable_objects.push_back(dwo);
}

void ShadingTestScene::SetupCamera()
{
    this->camera = new Camera(glm::vec3(0.0f, 0.0f, -4.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}


ShadingTestScene::ShadingTestScene(std::string shader_type, std::string shader_path, int width, int height, const char *title)
: Scene(shader_path, width, height, title)
{
    this->shader_type = shader_type;
    SetupCamera();
    shader_factory = new ShaderFactory(shader_path, camera);
    camera->SetupProjectionPerspective(width / (float)height, 1.0f, 100.0f);
}
