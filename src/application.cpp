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

    for (Model *model : this->models)
    {
        delete model;
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
        // Shader *triangle_shader = new Shader("shaders/triangle_v.glsl", "shaders/triangle_f.glsl");
        // shaders.push_back(triangle_shader);

        Shader *normale_shader = new Shader("shaders/normale_v.glsl", "shaders/normale_f.glsl");
        shaders.push_back(normale_shader);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
}

void Application::CreateModels()
{
    // Tree* tree = new Tree();
    // models.push_back(tree);
    Sphere* sphere = new Sphere();
    models.push_back(sphere);
    // Bushes* bushes = new Bushes();
    // models.push_back(bushes);
    // SuziFlat* suzi = new SuziFlat();
    // models.push_back(suzi);
    // float a[] = {
    //     -.5f, -.5f, .5f, 1, 0, 1,
    //     -.5f, .5f, .5f, 0, 1, 1,
    //     .5f, .5f, .5f, 0, 0, 1};
    // Triangle *triangle = new Triangle(a);
    // models.push_back(triangle);
}

void Application::Run()
{
    // glEnable(GL_DEPTH_TEST);

    glm::mat4 M = glm::mat4(1.0f); // construct identity matrix
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (Model *model : models)
        {
            Shader *shader;
            shader = shaders[0];
            model->Draw(shader, M);
        }

        // update other events like input handling
        glfwPollEvents();
        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cerr << "OpenGL error: " << error << std::endl;
        }
    }
}