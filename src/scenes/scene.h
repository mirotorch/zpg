#ifndef SCENE
#define SCENE

#include "../model.h"
#include "../shaderFactory.h"
#include "../drawableObject.h"
#include <vector>
#include <memory>

class Scene
{
private:
    GLFWwindow* window;
protected:
    std::vector<DrawableObject*> drawable_objects;
    ShaderFactory* shader_factory;
    virtual void UpdateTransformations() = 0;
public:
    Scene(std::string shader_path, int width, int height, const char* title);
    Scene(std::string shader_path, GLFWwindow* window);
    void SetAsCurrent();
    virtual void CreateDrawableObjects() = 0;
    int Draw();
    ~Scene();
};

#endif