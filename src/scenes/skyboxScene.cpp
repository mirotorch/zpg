#include "skyboxScene.h"
#include "../models/skycube.h"

SkyboxScene::SkyboxScene(std::string shader_path, GLFWwindow *window)
    : Scene(shader_path, window)
{
    SetupCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    skybox = new Skybox(this->camera, glm::vec3(50.0f, 50.0f, 50.0f));
}

void SkyboxScene::CreateDrawableObjects()
{
}

void SkyboxScene::Draw()
{
    skybox->Draw();
}
