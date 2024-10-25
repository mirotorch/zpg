#include "sphereScene.h"
#include "../models/sphere.h"

void SphereScene::UpdateTransformations()
{
}

void SphereScene::CreateDrawableObjects()
{
    std::vector<float> sphere_vertices(sphere, sphere + sizeof(sphere) / sizeof(float));

    Transformation* s_trans[4] = 
    {
        new CompoundTransformation(std::vector<Transformation*> 
        {
            new Translation(glm::vec3(1.5f, 0.0f, 0.0f)),
            new Scaling(glm::vec3(0.8f))
        }),
        new CompoundTransformation(std::vector<Transformation*> 
        {
            new Translation(glm::vec3(-1.5f, 0.0f, 0.0f)),
            new Scaling(glm::vec3(0.8f))
        }),
        new CompoundTransformation(std::vector<Transformation*> 
        {
            new Translation(glm::vec3(0.0f, 1.5f, 0.0f)),
            new Scaling(glm::vec3(0.8f))
        }),
        new CompoundTransformation(std::vector<Transformation*> 
        {
            new Translation(glm::vec3(0.0f, -1.5f, 0.0f)),
            new Scaling(glm::vec3(0.8f))
        })
    };
    for (int i = 0; i < 4; i++)
    {
        DrawableObject* dwo = new DrawableObject();
        dwo->model = new Model(sphere_vertices, 2880);
        dwo->transformation = s_trans[i];
        dwo->shader = shader_factory->GetShader("lambert_v", "lambert_f");
        drawable_objects.push_back(dwo);
    }
}

void SphereScene::SetupCamera()
{
    this->camera = new Camera(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void SphereScene::HandleKeyboardInput(int key, int scancode, int action, int mods)
{
}

void SphereScene::HandleMouseInput(double xpos, double ypos)
{
}

SphereScene::SphereScene(std::string shader_path, int width, int height, const char *title)
: Scene(shader_path, width, height, title)
{
    SetupCamera();
    shader_factory = new ShaderFactory(shader_path, camera);
    camera->SetupProjectionPerspective(width / (float)height, 1.0f, 100.0f);
}
