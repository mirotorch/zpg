#include "suziScene.h"
#include "../models/suzi_flat.h"
#include "../models/suzi_smooth.h"
#include "../models/gift.h"

void SuziScene::CreateDrawableObjects()
{
    std::vector<ShaderProgram*> programs = 
    {
        shader_factory->GetShader("lambert_v", "lambert_f"),
        shader_factory->GetShader("phong_v", "phong_f"),
        shader_factory->GetShader("phong_v", "blinn_f"),
    };
    std::vector<std::vector<float>> vertices = 
    {
        std::vector<float>(suziFlat, suziFlat + sizeof(suziFlat) / sizeof(float)),
        std::vector<float>(suziSmooth, suziSmooth + sizeof(suziSmooth) / sizeof(float)),
        std::vector<float>(gift, gift + sizeof(gift) / sizeof(float)),
    };
    std::vector<size_t> sizes = 
    {
        2904,
        2904,
        66624
    };

    Transformation* s_trans[4] = 
    {
        new CompoundTransformation(std::vector<Transformation*> 
        {
            new Translation(glm::vec3(2.0f, 0.0f, 0.0f)),
            new Scaling(glm::vec3(0.8f)),
            new Rotation(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        }),
        new CompoundTransformation(std::vector<Transformation*> 
        {
            new Translation(glm::vec3(-2.0f, 0.0f, 0.0f)),
            new Scaling(glm::vec3(0.8f)),
            new Rotation(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        }),
        new CompoundTransformation(std::vector<Transformation*> 
        {
            new Translation(glm::vec3(0.0f, 2.0f, 0.0f)),
            new Scaling(glm::vec3(1.5f)),
            new Rotation(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
            new Rotation(glm::radians(140.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        }),
    };
    for (int i = 0; i < 3; i++)
    {
        DrawableObject* dwo = new DrawableObject();
        dwo->model = new Model(vertices[i], sizes[i]);
        dwo->transformation = s_trans[i];
        dwo->shader = programs[i];
        drawable_objects.push_back(dwo);
    }
}



SuziScene::SuziScene(std::string shader_path, GLFWwindow* window)
: Scene(shader_path, window)
{
    SetupCamera(glm::vec3(0.0f, 0.0f, -8.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
