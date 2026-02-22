#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/renderer/renderer.h"
class Window;
class Application
{
public:
    Application();
    static void terminate();
    static bool isGlfwInitialized();
    void setWindow(Window* w);
    bool run();
    void setRenderer(Renderer* renderer);
private:
    Window* window = nullptr;
    static bool glfwInitialized;
    Renderer* _renderer = nullptr;
};

#endif // APPLICATION_H
