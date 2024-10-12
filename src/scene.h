#ifndef SCENE
#define SCENE

#include "models/triangle.h"
#include "models/rectangle.h"
#include "models/sphere.h"
#include <vector>

class Scene
{
private:
    std::vector<Model*> models;
    std::vector<Shader*> shaders;
    GLFWwindow* window;
    
    static void error_callback(int error, const char* description);
public:
    Scene(int width, int height, const char* title);
    void CreateShaders();
    void CreateModels();
    void Run();
    ~Scene();
};

#endif