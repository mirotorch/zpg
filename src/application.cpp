#include "application.h"

void Application::error_callback(int error, const char *description)
{
    fputs(description, stderr);
}

Application::Application(int width, int height, const char *title)
{
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }
    glfwSetErrorCallback(error_callback);

    this->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!this->window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    // get version info
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    float ratio = w / (float)h;
    glViewport(0, 0, w, h);
}

Application::~Application()
{
    glfwDestroyWindow(this->window);

    for (Figure *figure : this->figures)
    {
        delete figure;
    }

    for (Shader *shader : this->shaders)
    {
        delete shader;
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Application::CreateShaders()
{
    try
    {
        Shader *triangle_shader = new Shader("shaders/triangle_v.glsl", "shaders/triangle_f.glsl");
        shaders.push_back(triangle_shader);

        Shader *rectangle_shader = new Shader("shaders/triangle_v.glsl", "shaders/rectangle_f.glsl");
        shaders.push_back(rectangle_shader);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
}

void Application::CreateModels()
{
    Triangle* test = new Triangle(
        Point(-0.2f, -0.3f, 0.0f),
        Point(-0.2f, -0.7f, 0.0f),
        Point(-0.4f, -0.4f, 0.0f)
    );
    test->shaders = shaders[0];
    figures.push_back(test);

    Rectangle* square = new Rectangle(
        Point(0.0f, 0.0f, 0.0f),
        Point(0.9f, 0.9f, 0.0f)
    );
    square->shaders = shaders[1];
    figures.push_back(square);
}

void Application::Run()
{
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (Figure* figure : figures)
        {
            figure->Draw();
        }

        // update other events like input handling
        glfwPollEvents();
        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window);
    }
}