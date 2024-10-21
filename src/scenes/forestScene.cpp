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
        drawable->model = new Model(tree, size);
    }
    else
    {
        size_t size = sizeof(bushes) / sizeof(float);
        drawable->model = new Model(bushes, size);
    }
    drawable->shader = shader_factory->GetShader("camera_v", "normale_f");
    drawable->t_model = ct;
    drawable_objects.push_back(drawable);
}

void ForestScene::CreateDrawableObjects()
{
    SetAsCurrent();

    CreateForest(40, 20);
}

void ForestScene::HandleKeyboardInput(int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W) camera->ToFront();
    else if (key == GLFW_KEY_S) camera->ToBack();
    else if (key == GLFW_KEY_A) camera->ToLeft();
    else if (key == GLFW_KEY_D) camera->ToRight();
}

void ForestScene::HandleMouseInput(double x_pos, double y_pos)
{
    if (first_mouse) 
    {
        last_x = x_pos;
        last_y = y_pos;
        first_mouse = false;
        return;
    }

    float xoffset = x_pos - last_x;
    float yoffset = last_y - y_pos;

    last_x = x_pos;
    last_y = y_pos;

    camera->Rotate(xoffset * rotation_speed, yoffset * rotation_speed); 
}


ForestScene::ForestScene(std::string shader_path, int width, int height, const char *title) 
: Scene(shader_path, width, height, title)
{
    // float aspect = width / (float)height;
    camera->SetupProjectionPerspective(1.0f, 1.0f, 100.0f);
}
