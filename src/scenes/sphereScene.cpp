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
        dwo->shader = shader_factory->GetShader("phong_v", "blinn_multiple_f");
        Material m = Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(0.5f), 32);
        dwo->material = m;
        drawable_objects.push_back(dwo);
    }
    shader_factory->GetShader("phong_v", "blinn_multiple_f")->AddLight(
        PointLight(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(1.0f), 1.0f, 0.18f, 0.064f));


    // Login + DirLight demonstration
    drawable_objects.push_back(new DrawableObject(
        new Model("login.obj"),
        shader_factory->GetShader("phong_v", "phong_multiple_f"),
        new CompoundTransformation(
            std::vector<Transformation*> {
                new Translation(glm::vec3(0.0f, 0.0f, 10.0f)),
                new Rotation(glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f))
            }
        ),
        Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(0.5f), 32)
    ));
    shader_factory->GetShader("phong_v", "phong_multiple_f")->AddLight(
        DirLight(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f))
    );
}

void SphereScene::HandleMouseButtonInput(double x_pos, double y_pos, int button)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        auto light = Spotlight(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), glm::cos(glm::radians(12.0f)),
            glm::cos(glm::radians(17.0f)), 1.0f, 0.18f, 0.064f, true);
        shader_factory->GetShader("phong_v", "phong_multiple_f")->AddLight(light);
        shader_factory->GetShader("phong_v", "blinn_multiple_f")->AddLight(light);
    }
}

SphereScene::SphereScene(std::string shader_path, GLFWwindow* window)
: Scene(shader_path, window)
{
    SetupCamera(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
