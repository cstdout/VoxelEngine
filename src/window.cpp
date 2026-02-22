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
