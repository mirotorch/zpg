#include "application.h"

int main() 
{
    Application* app = new Application(800, 600, "ZPG");

    app->CreateShaders();
    app->CreateModels();

    app->Run();

    delete app;
    return 0;
}