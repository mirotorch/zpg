#include "forestScene.hpp"
#include <glm/gtc/constants.hpp> 
#include <random>


void ForestScene::UpdateTransformations()
{
}

void ForestScene::CreateForest(int trees, int bushes)
{
    std::random_device rd; 
    std::mt19937 gen(rd());
    
    std::uniform_real_distribution<float> translation_dist(-70, 70);
    std::uniform_real_distribution<float> scaling_dist(1.0f, 5.0f);
    std::uniform_real_distribution<float> angle_dist(0.0f, glm::two_pi<float>()); 

    for (int i = 0; i < trees + bushes; ++i)
    {
        glm::vec3 translation(translation_dist(gen), 0.0f, translation_dist(gen));
        glm::vec3 scaling(scaling_dist(gen), scaling_dist(gen), scaling_dist(gen));
        float angle = angle_dist(gen);
        glm::vec3 rotation_axis = glm::normalize(glm::vec3(0.0f, translation_dist(gen), 0.0f));

        CompoundTransformation* ct = new CompoundTransformation(std::vector<Transformation*>
        {
            new Translation(translation),
            new Scaling(scaling),
            new Rotation(angle, rotation_axis)
        });

        SaveDrawableObject(ct, i <= trees);
    }
}

void ForestScene::SaveDrawableObject(Transformation* ct, bool is_tree)
{
    auto drawable = new DrawableObject();
    if (is_tree) 
    {
        size_t size = sizeof(tree) / sizeof(float);
        drawable->model = new Model(tree, size, 92814);
    }
    else
    {
        size_t size = sizeof(bushes) / sizeof(float);
        drawable->model = new Model(bushes, size, 92814);
    }
    drawable->shader = shader_factory->GetShader("phong_v", "phong_f");
    drawable->transformation = ct;
    drawable_objects.push_back(drawable);
}

void ForestScene::CreateDrawableObjects()
{
    SetAsCurrent();
    // CompoundTransformation* ct = new CompoundTransformation(std::vector<Transformation*>
    // {
    // });
    // SaveDrawableObject(ct, true);
    CreateForest(40, 20);
}

void ForestScene::SetupCamera() 
{
    this->camera = new Camera(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}


ForestScene::ForestScene(std::string shader_path, int width, int height, const char *title) 
: DynamicScene(shader_path, width, height, title)
{
    // float aspect = width / (float)height;
    SetupCamera();
    shader_factory = new ShaderFactory(shader_path, camera);
    camera->SetupProjectionPerspective(1.0f, 1.0f, 100.0f);
}
