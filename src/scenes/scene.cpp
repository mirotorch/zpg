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

void Scene::LoadTextures(std::vector<std::string> names)
{
    for (const auto& name : names)
    {
        textures.push_back(TextureManager::GetTextureId(name));
    }
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
    if (skybox != nullptr)
    {
        delete skybox;
    }
    delete camera;
}

void Scene::Draw()
{
    if (skybox != nullptr) skybox->Draw();
    for (int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE1 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
    }
    for (const auto &drawable : drawable_objects)
    {
        drawable->Draw();
    }
}

void Scene::ToggleSkybox()
{
    if (skybox != nullptr)
    {
        skybox->move = !skybox->move;
    }
}

void Scene::SetupProjectionPerspective(int w, int h)
{
    float ratio = w / (float)h;
    camera->SetupProjectionPerspective(ratio, 1.0f, 100.0f);
}

void Scene::HandleKeyboardInput(int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action != GLFW_RELEASE) camera->ToFront();
    else if (key == GLFW_KEY_S && action != GLFW_RELEASE) camera->ToBack();
    else if (key == GLFW_KEY_A && action != GLFW_RELEASE) camera->ToLeft();
    else if (key == GLFW_KEY_D && action != GLFW_RELEASE) camera->ToRight();
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

void Scene::HandleMouseButtonInput(double x_pos, double y_pos, int button)
{
}
