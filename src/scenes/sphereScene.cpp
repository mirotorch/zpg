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
        dwo->shader = shader_factory->GetShader("phong_v", "phong_multiple_f");
        Material m;
        m.ambient = glm::vec3(0.1f);
        m.diffuse = glm::vec3(1.0f);
        m.specular = glm::vec3(0.5f);
        m.shininess = 32;
        dwo->material = m;
        drawable_objects.push_back(dwo);
    }

    PointLight l;
    l.color = glm::vec3(1.0f);
    l.position = glm::vec3(0.0f);
    l.constant = 0.1;
    l.linear = 0.5;
    l.quadratic = 1;
    shader_factory->GetShader("phong_v", "phong_multiple_f")->AddLight(l);
    DirLight dl;
    dl.color = glm::vec3(1.0f);
    dl.direction = glm::vec3(1, 0, 0);
    // shader_factory->GetShader("phong_v", "phong_multiple_f")->AddLight(dl);
    // shader_factory->GetShader("phong_v", "phong_multiple_f")->AddLight(NewPointLight(glm::vec3(2.0f), glm::vec3(1.0f), 0.1, 1, 1));
}


SphereScene::SphereScene(std::string shader_path, GLFWwindow* window)
: Scene(shader_path, window)
{
    SetupCamera(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
