#include "scene.h"

void Scene::Init(std::string title, std::string shader_path)
{
    camera = new Camera();
    shader_factory = new ShaderFactory(shader_path, camera);

    if (!this->window)
    {
        std::cerr << "Window " << title << " failed to initialize" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    float ratio = w / (float)h;
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
}

void Scene::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
    if (scene) scene->HandleKeyboardInput(key, scancode, action, mods);
}

void Scene::MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
    if (scene) scene->HandleMouseInput(xpos, ypos);
}

Scene::Scene(std::string shader_path, int width, int height, const char *title)
{
    this->window = glfwCreateWindow(width, height, title, NULL, NULL);
    Init(title, shader_path);
}

Scene::Scene(std::string shader_path, GLFWwindow *window)
{
    this->window = window;
    Init("", shader_path);
}

void Scene::SetAsCurrent()
{
    glfwMakeContextCurrent(window);
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
    glfwDestroyWindow(this->window);
}

int Scene::Draw()
{
    SetAsCurrent();
    if (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        UpdateTransformations();

        for (const auto& drawable : drawable_objects)
        {
            drawable->Draw();
        }

        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cerr << "OpenGL error: " << error << std::endl;
        }
        return error;
    }
    else
    {
        return -1;
    }
}
