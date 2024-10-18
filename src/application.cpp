#include "application.h"

void Application::error_callback(int error, const char *description)
{
    fputs(description, stderr);
}

void Application::PrintInfo()
{
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

Application::Application()
{
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }
    glfwSetErrorCallback(error_callback);

}

Application::~Application()
{
    scenes.clear(); 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


void Application::CreateScenes()
{
    std::unique_ptr<Scene> forest(new ForestScene(shader_path, 1400, 700, "forest"));
    forest->CreateDrawableObjects();
    scenes.push_back(std::move(forest));

    // std::unique_ptr<Scene> sphere(new SphereScene(shader_path, 800, 600, "sphere"));
    // sphere->CreateDrawableObjects();
    // scenes.push_back(std::move(sphere));
}

void Application::Run()
{
    while (!scenes.empty())
    {
        for (auto it = scenes.begin(); it != scenes.end();)
        {
            Scene *scene = it->get();
            if (scene->Draw() != 0)
            {
                it = scenes.erase(it);
            }
            else
            {
                ++it;
            }
        }
        // update other events like input handling
        glfwPollEvents();
    }
}