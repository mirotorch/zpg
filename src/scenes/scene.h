#ifndef SCENE
#define SCENE

#include "../model.h"
#include "../shaderFactory.h"
#include "../drawableObject.h"
#include "../camera.h"
#include "../textureManager.h"
#include <vector>
#include <memory>

class Scene
{
protected:
    GLFWwindow* window;
    std::vector<DrawableObject*> drawable_objects;
    ShaderFactory* shader_factory;
    std::string shader_path;

    Camera* camera;
    virtual void SetupCamera(glm::vec3 x, glm::vec3 y, glm::vec3 z);
    
    std::vector<GLuint> textures;
    virtual void LoadTextures(std::vector<std::string> names);

    float last_y;
    float last_x;
    bool first_mouse = true;
    const float rotation_speed = 0.1f;
public:
    Scene(std::string shader_path, GLFWwindow* window);
    virtual void CreateDrawableObjects() = 0;
    void HandleKeyboardInput(int key, int scancode, int action, int mods);
    void HandleMouseInput(double x_pos, double y_pos);
    void SetupProjectionPerspective(int w, int h);
    virtual void Draw();
    ~Scene();
};

#endif