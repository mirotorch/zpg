#ifndef SCENE
#define SCENE

#include "../models/model.h"
#include "../shaderFactory.h"
#include <vector>
#include <memory>

class Scene
{
private:
    GLFWwindow* window;
protected:
    typedef struct DrawableObject
    {
        Model* model;
        Shader* shader;
        glm::mat4 transformation;

        void Draw()
        {
            model->Draw(shader, transformation);
        }
    } DrawableObject;

    std::vector<std::shared_ptr<DrawableObject>> drawable_objects;
    ShaderFactory* shader_factory;
    virtual void UpdateTransformations() = 0;
public:
    Scene(ShaderFactory* shader_factory, int width, int height, const char* title);
    void SetAsCurrent();
    virtual void CreateDrawableObjects() = 0;
    int Draw();
    ~Scene();
};

#endif