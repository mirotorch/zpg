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
protected:
    GLFWwindow* window;
    std::vector<DrawableObject*> drawable_objects;
    ShaderFactory* shader_factory;
    Camera* camera;
    virtual void SetupCamera(glm::vec3 x, glm::vec3 y, glm::vec3 z);
    std::string shader_path;

    float last_y;
    float last_x;
    bool first_mouse = true;
    const float rotation_speed = 0.1f;
public:
    Scene(std::string shader_path, GLFWwindow* window);
    virtual void CreateDrawableObjects() = 0;
    void HandleKeyboardInput(int key, int scancode, int action, int mods);
    void HandleMouseInput(double x_pos, double y_pos);
    virtual void Draw();
    ~Scene();
};

#endif