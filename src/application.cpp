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
bool Application::run()
{
    if(window == nullptr)
    {
        std::cerr << "Window was not set" << std::endl;
        return false;
    }
    if(_renderer == nullptr)
    {
        std::cerr << "Renderer was not set" << std::endl;
        return false;
    }
    window->create();

    bool windowCursorDisabled = window->isCursorDisabled();
    glfwSetInputMode(window->_window, GLFW_CURSOR, windowCursorDisabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);

    _renderer->init();
    if(!(_renderer->isInitialized()))
    {
        std::cerr << "Renderer was not initialized" << std::endl;
        return false;
    }

    float currentFrame, deltaTime;
    float lastFrame = 0.0f;
    while(!(window->isShouldClose()))
    {
        currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // For multiple windows in the future may be
        window->makeContextCurrent();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
        _renderer->render(deltaTime, window->width(), window->height());

        window->swapBuffers();
        glfwPollEvents();

    }
    window->opened = false;
    terminate();
    return true;
}

