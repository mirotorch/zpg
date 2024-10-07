#ifndef APPLICATION
#define APPLICATION

#include "models/triangle.h"
#include "models/rectangle.h"
#include <vector>

class Application
{
private:
    std::vector<Model*> models;
    std::vector<Shader*> shaders;
    GLFWwindow* window;
    
    static void error_callback(int error, const char* description);
public:
    Application(int width, int height, const char* title);
    void CreateShaders();
    void CreateModels();
    void Run();
    ~Application();
};

#endif