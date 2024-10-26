#include "dynamicScene.h"

void DynamicScene::HandleKeyboardInput(int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W) camera->ToFront();
    else if (key == GLFW_KEY_S) camera->ToBack();
    else if (key == GLFW_KEY_A) camera->ToLeft();
    else if (key == GLFW_KEY_D) camera->ToRight();
}

void DynamicScene::HandleMouseInput(double x_pos, double y_pos)
{
    if (first_mouse) 
    {
        last_x = x_pos;
        last_y = y_pos;
        first_mouse = false;
        return;
    }

    float xoffset = x_pos - last_x;
    float yoffset = last_y - y_pos;

    last_x = x_pos;
    last_y = y_pos;

    camera->Rotate(xoffset * rotation_speed, yoffset * rotation_speed); 
}


void DynamicScene::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    DynamicScene* scene = static_cast<DynamicScene*>(glfwGetWindowUserPointer(window));
    if (scene) scene->HandleKeyboardInput(key, scancode, action, mods);
}

void DynamicScene::MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    DynamicScene* scene = static_cast<DynamicScene*>(glfwGetWindowUserPointer(window));
    if (scene) scene->HandleMouseInput(xpos, ypos);
}

DynamicScene::DynamicScene(std::string shader_path, int width, int height, const char *title)
: Scene(shader_path, width, height, title)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
}

DynamicScene::DynamicScene(std::string shader_path, GLFWwindow* window)
: Scene(shader_path, window)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
}
