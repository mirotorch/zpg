#ifndef APPLICATION
#define APPLICATION

#include "scenes/testScene.hpp"
#include "shaderFactory.h"
#include <vector>
#include <memory>

class Application
{
private:
    std::vector<std::unique_ptr<Scene>> scenes;
    ShaderFactory* shader_factory;
    static void error_callback(int error, const char* description);
public:
    void PrintInfo();
    Application();
    void CreateScenes();
    void Run();
    ~Application();
};

#endif