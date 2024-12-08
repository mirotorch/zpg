#ifndef APPLICATION
#define APPLICATION

#include "shaderFactory.h"
#include "scenes/scene.h"
#include <vector>
#include <memory>

class Application
{
private:
    GLFWwindow* main_window;
    std::vector<Scene*> scenes;
    int active_scene_index = -1;
    const std::string shader_path = "shaders/";
    void HandleKeyboardOutput(int key, int scancode, int action, int mods);
    void HandleMouseOutput(double x_pos, double y_pos);
    void HadnleMouseButtonOutput(int button, int action, int mods);
    void HandleWindowResize(int w, int h);
public:
    Application();
    void PrintInfo();
    void CreateScenes();
    void Run();
    static void error_callback(int error, const char* description);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseCallback(GLFWwindow* window, double x_pos, double y_pos);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void WindowSizeCallback(GLFWwindow* window, int width, int height);
    ~Application();
};

#endif