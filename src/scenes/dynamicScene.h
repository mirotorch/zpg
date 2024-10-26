#pragma once

#include "scene.h"

class DynamicScene : public Scene
{
private:
    void HandleKeyboardInput(int key, int scancode, int action, int mods);
    void HandleMouseInput(double x_pos, double y_pos);
    float last_y;
    float last_x;
    bool first_mouse = true;
    const float rotation_speed = 0.1f;
public:
    DynamicScene(std::string shader_path, int width, int height, const char *title);
    DynamicScene(std::string shader_path, GLFWwindow* window);

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseCallback(GLFWwindow* window, double x_pos, double y_pos);
};