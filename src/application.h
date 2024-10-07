#ifndef APPLICATION
#define APPLICATION

#include "figures/triangle.h"
#include "figures/rectangle.h"
#include <vector>

class Application
{
private:
    std::vector<Figure*> figures;
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