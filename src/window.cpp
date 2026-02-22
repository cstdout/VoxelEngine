#include <iostream>
#include "window.h"

Window::Window(int32_t width, int32_t height, const std::string& title)
{
    initialize(width, height, title.c_str());
}
Window::Window(int32_t width, int32_t height, const char* title)
{
    initialize(width, height, title);
}
int32_t Window::initialize(int32_t width, int32_t height, const char* title)
{

    _width = width;
    _height = height;
    _title = title;

//    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


    return 0;
}
int32_t Window::width() const
{
    return _width;
}
int32_t Window::height() const
{
    return _height;
}
std::string& Window::title() const
{
    std::string* t = new std::string(_title);
    return *t;
}
int32_t Window::create()
{
    _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
    if (_window == nullptr)
    {
        std::cerr << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    glViewport(0, 0, _width, _height);

    //TODO: set event callbacks

    opened = true;
    return 0;
}
bool Window::isOpened() const
{
    return opened;
}
bool Window::isShouldClose() const
{
    return glfwWindowShouldClose(_window);
}
void Window::close()
{
    glfwSetWindowShouldClose(_window, true);
}
void Window::makeContextCurrent()
{
    glfwMakeContextCurrent(_window);
}
void Window::swapBuffers()
{
    glfwSwapBuffers(_window);
}
bool Window::isCreated() const
{
    return (_window != nullptr);
}
void Window::setCursorDisabled(bool v)
{
    _cursorDisabled = v;
}
