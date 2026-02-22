#include <iostream>
#include "application.h"
#include "window.h"

bool Application::glfwInitialized = false;
Application::Application()
{
    if (!(Application::glfwInitialized) && glfwInit() == GLFW_TRUE)
    {
        Application::glfwInitialized = true;
    }
}
bool Application::isGlfwInitialized()
{
    return Application::glfwInitialized;
}
void Application::terminate()
{
    glfwTerminate();
}
void Application::setWindow(Window *w)
{
    window = w;
}
void Application::setRenderer(Renderer *renderer)
{
    _renderer = renderer;
}
