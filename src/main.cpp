#include "application.h"

int main() 
{
    Application* app = new Application();

    app->CreateScenes();
    app->PrintInfo();
    app->Run();

    delete app;
    return 0;
}