#ifndef APPLICATION
#define APPLICATION

#include "scenes/forestScene.hpp"
#include "shaderFactory.h"
#include <vector>
#include <memory>

class Application
{
private:
    std::vector<std::unique_ptr<Scene>> scenes;
    const std::string shader_path = "shaders/";
    static void error_callback(int error, const char* description);
public:
    void PrintInfo();
    Application();
    void CreateScenes();
    void Run();
    ~Application();
};

#endif