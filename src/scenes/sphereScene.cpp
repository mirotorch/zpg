#include "sphereScene.h"
#include "../models/sphere.h"

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
        dwo->shader = shader_factory->GetShader("phong_v", "phong_f");
        drawable_objects.push_back(dwo);
    }

    Light l;
    l.color = glm::vec3(1.0f);
    l.position = glm::vec3(0.0f);
    shader_factory->GetShader("phong_v", "phong_f")->AddLight(l);
}


SphereScene::SphereScene(std::string shader_path, GLFWwindow* window)
: Scene(shader_path, window)
{
    SetupCamera(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
