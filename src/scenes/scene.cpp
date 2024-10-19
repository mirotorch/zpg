#include "scene.h"

Scene::Scene(std::string shader_path, int width, int height, const char *title)
{
    shader_factory = new ShaderFactory(shader_path);

    this->window = glfwCreateWindow(width, height, title, NULL, NULL);
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
}

Scene::Scene(std::string shader_path, GLFWwindow *window)
{
    this->window = window;
    shader_factory = new ShaderFactory(shader_path);

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
