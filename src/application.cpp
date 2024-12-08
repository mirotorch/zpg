#include "application.h"
#include "scenes/sphereScene.h"
#include "scenes/forestScene.h"
#include "scenes/shadingTestScene.h"
#include "scenes/suziScene.h"
#include "scenes/textureScene.h"
#include "scenes/skyboxScene.h"

void Application::error_callback(int error, const char *description)
{
    fputs(description, stderr);
}

void Application::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) app->HandleKeyboardOutput(key, scancode, action, mods);
}

void Application::MouseCallback(GLFWwindow *window, double x_pos, double y_pos)
{    
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) app->HandleMouseOutput(x_pos, y_pos);
}

void Application::WindowSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) app->HandleWindowResize(width, height);
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

void Application::HandleKeyboardOutput(int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        if (glfwGetInputMode(main_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
        {
            glfwSetInputMode(main_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } 
        else 
        {
            glfwSetInputMode(main_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS && scenes.size() > 0)
    {
        if (active_scene_index + 1 >= scenes.size())
            active_scene_index = 0;
        else active_scene_index++;
        int w, h;
        glfwGetFramebufferSize(main_window, &w, &h);
        scenes[active_scene_index]->SetupProjectionPerspective(w, h);
    }
    else
    {
        if (active_scene_index >= 0)
            scenes[active_scene_index]->HandleKeyboardInput(key, scancode, action, mods);
    }
}

void Application::HandleMouseOutput(double x_pos, double y_pos)
{
    if (glfwGetInputMode(main_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED && active_scene_index >= 0)
        scenes[active_scene_index]->HandleMouseInput(x_pos, y_pos);
}

void Application::HandleWindowResize(int w, int h)
{
    scenes[active_scene_index]->SetupProjectionPerspective(w, h);
}

Application::Application()
{
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }
    glfwSetErrorCallback(error_callback);

    this->main_window = glfwCreateWindow(1400, 700, "main", NULL, NULL);
    if (!this->main_window)
    {
        std::cerr << "Window main" << " failed to initialize" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(main_window);
    glfwSwapInterval(1);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    int w, h;
    glfwGetFramebufferSize(main_window, &w, &h);
    float ratio = w / (float)h;
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);

    glfwSetWindowUserPointer(main_window, this);
    glfwSetKeyCallback(main_window, KeyCallback);
    glfwSetCursorPosCallback(main_window, MouseCallback);
    glfwSetFramebufferSizeCallback(main_window, WindowSizeCallback);
}

Application::~Application()
{
    for (int i = 0; i < scenes.size(); i++)
        delete scenes[i];
    TextureManager::Clear();
    glfwDestroyWindow(this->main_window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Application::CreateScenes()
{
    // ForestScene* forest = new ForestScene(shader_path, main_window);
    // forest->CreateDrawableObjects();
    // scenes.push_back(forest);
    // SphereScene* sphere = new SphereScene(shader_path, main_window);
    // sphere->CreateDrawableObjects();
    // scenes.push_back(sphere);

    // TextureScene* texture = new TextureScene(shader_path, main_window);
    // texture->CreateDrawableObjects();
    // scenes.push_back(texture);

    SkyboxScene* skybox = new SkyboxScene(shader_path, main_window);
    skybox->CreateDrawableObjects();
    scenes.push_back(skybox);

    active_scene_index = 0;
}

void Application::Run()
{
    while (!glfwWindowShouldClose(main_window))
    {
        if (active_scene_index >= 0)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            scenes[active_scene_index]->Draw();

            // put the stuff we’ve been drawing onto the display
            glfwSwapBuffers(main_window);
            GLenum error = glGetError();
            if (error != GL_NO_ERROR)
            {
                std::cerr << "OpenGL error: " << error << std::endl;
                break;
            }
        }
        // update other events like input handling
        glfwPollEvents();
    }
}