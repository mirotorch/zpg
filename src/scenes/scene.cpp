#include "scene.h"

void Scene::SetupCamera(glm::vec3 x, glm::vec3 y, glm::vec3 z)
{
    this->camera = new Camera(x, y, z);
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    float ratio = w / (float)h;
    camera->SetupProjectionPerspective(ratio, 1.0f, 100.0f);
    shader_factory = new ShaderFactory(shader_path, camera);
}

Scene::Scene(std::string shader_path, GLFWwindow *window)
{
    this->window = window;
    this->shader_path = shader_path;
}

Scene::~Scene()
{
    for (const auto& drawable : drawable_objects)
    {
        delete drawable;
    }
    drawable_objects.clear();
    delete shader_factory;
    delete camera;
}

void Scene::Draw()
{
    for (const auto &drawable : drawable_objects)
    {
        drawable->Draw();
    }
}

void Scene::HandleKeyboardInput(int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W) camera->ToFront();
    else if (key == GLFW_KEY_S) camera->ToBack();
    else if (key == GLFW_KEY_A) camera->ToLeft();
    else if (key == GLFW_KEY_D) camera->ToRight();
}

void Scene::HandleMouseInput(double x_pos, double y_pos)
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
