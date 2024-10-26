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
    void Init(std::string title, std::string shader_path);
protected:
    GLFWwindow* window;
    std::vector<DrawableObject*> drawable_objects;
    ShaderFactory* shader_factory;
    Camera* camera;
    virtual void UpdateTransformations() = 0;
    virtual void SetupCamera() = 0;
public:
    Scene(std::string shader_path, int width, int height, const char* title);
    Scene(std::string shader_path, GLFWwindow* window);
    void SetAsCurrent();
    virtual void CreateDrawableObjects() = 0;
    int Draw();
    ~Scene();
};

#endif