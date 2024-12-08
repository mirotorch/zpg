#include "sphereScene.h"
#include "../models/sphere.h"
#include "../movement/linearMovement.h"
#include "../movement/cubicBezierMovement.h"

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
        Material m = Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(0.5f), 32);
        dwo->material = m;
        drawable_objects.push_back(dwo);
    }
    drawable_objects[3]->movement = new LinearMovement(glm::vec3(0.0f), glm::vec3(0.0f, -10.0f, 0.0f), 0.001f);
    drawable_objects[2]->movement = new CubicBezierMovement(
        glm::vec3(0.0f), glm::vec3(0.0f, 5.0f, 3.0f),
        glm::vec3(2.0f, 8.0f, 1.0f), glm::vec3(3.0f, 8.0f, 12.0f), 0.01
    );
    shader_factory->GetShader("phong_v", "phong_multiple_f")->AddLight(Spotlight(
        glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(1.0f), glm::radians(10.0f), glm::radians(10.1f), 1.0f, 0.18f, 0.064f, true
    ));
    // shader_factory->GetShader("phong_v", "phong_multiple_f")->AddLight(PointLight(glm::vec3(2.0f), glm::vec3(1.0f), 0.1, 1, 1));
}


SphereScene::SphereScene(std::string shader_path, GLFWwindow* window)
: Scene(shader_path, window)
{
    SetupCamera(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
