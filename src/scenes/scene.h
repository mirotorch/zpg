#ifndef SCENE
#define SCENE

#include "../model.h"
#include "../shaderFactory.h"
#include "../drawableObject.h"
#include "../camera.h"
#include <vector>
#include <memory>

class Scene
{
private:
    GLFWwindow* window;
    void Init(std::string title, std::string shader_path);
protected:
    std::vector<DrawableObject*> drawable_objects;
    ShaderFactory* shader_factory;
    Camera* camera;
    virtual void UpdateTransformations() = 0;
    virtual void HandleKeyboardInput(int key, int scancode, int action, int mods) = 0;
    virtual void HandleMouseInput(double x_pos, double y_pos) = 0;
public:
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseCallback(GLFWwindow* window, double x_pos, double y_pos);
    Scene(std::string shader_path, int width, int height, const char* title);
    Scene(std::string shader_path, GLFWwindow* window);
    void SetAsCurrent();
    virtual void CreateDrawableObjects() = 0;
    int Draw();
    ~Scene();
};

#endif