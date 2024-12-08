#include "forestScene.h"
#include <glm/gtc/constants.hpp> 
#include <random>
#include "../movement/cubicBezierMovement.h"

void ForestScene::CreateForest(int trees, int bushes)
{
    std::random_device rd; 
    std::mt19937 gen(rd());
    
    std::uniform_real_distribution<float> translation_dist(10, 80);

    for (int i = 0; i < trees; ++i)
    {
        glm::vec3 translation(translation_dist(gen), 0.0f, translation_dist(gen));
        drawable_objects.push_back(new DrawableObject(
            new Model("tree.obj"),
            shader_factory->GetShader("phong_v", "textured_f"),
            new Translation(translation),
            Material(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.5f), 32),
            2
        ));
    }
}

void ForestScene::CreateDrawableObjects()
{
    CreateForest(40, 0);
    ShaderProgram* sp = shader_factory->GetShader("phong_v", "textured_f");
    drawable_objects.push_back(new DrawableObject(
        new Model("model.obj"),
        sp,
        new Translation(glm::vec3(10.0f, 0.0f, -15.0f)),
        Material(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.5f), 32),
        1
    ));
    drawable_objects.push_back(new DrawableObject(
        new Model("floor.obj"),
        sp,
        new Scaling(glm::vec3(100.0f, 1.0f, 100.0f)),
        Material(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.5f), 32),
        3
    ));

    drawable_objects.push_back(new DrawableObject(
        new Model("zombie.obj"),
        sp,
        new Translation(glm::vec3(-5.0f, 0.0f, -8.0f)),
        Material(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.5f), 32),
        4,
        new CubicBezierMovement(
            glm::vec3(0.0f), glm::vec3(-10.0f, 10.0f, 0.0f),
            glm::vec3(-10.0f, 0.0f, 10.0f), glm::vec3(0.0f), 
            0.01f
        )
    ));
}


void ForestScene::Draw()
{
    Scene::Draw();
}

void ForestScene::HandleMouseButtonInput(double x_pos, double y_pos, int button)
{
    GLbyte color[4];
    GLfloat depth;
    GLuint index;
    
    GLint x = (GLint)x_pos;
    GLint y = (GLint)y_pos;

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    int newy = height - y;
    
    glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
    
    printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
    glm::vec3 screenX = glm::vec3(x, newy, depth);
    glm::mat4 view = camera->GetView();
    glm::mat4 projection = camera->GetProjection();
    glm::vec4 viewPort = glm::vec4(0, 0, width, height);
    glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

    drawable_objects.push_back(new DrawableObject(
        new Model("tree.obj"),
        shader_factory->GetShader("phong_v", "textured_f"),
        new Translation(pos),
        Material(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.5f), 32),
        2
    ));
}

ForestScene::ForestScene(std::string shader_path, GLFWwindow* window) 
: Scene(shader_path, window)
{
    SetupCamera(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    skybox = new Skybox(this->camera, glm::vec3(2.0f, 2.0f, 2.0f));
    LoadTextures(std::vector<std::string> {"test.png", "tree.png", "grass.png", "zombie.png"});
}
