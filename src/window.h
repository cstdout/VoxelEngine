#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>
#include "application.h"
class Window
{
public:
    Window(int32_t width, int32_t height, const std::string& title);
    Window(int32_t width, int32_t height, const char* title);


    int32_t initialize(int32_t width, int32_t height, const char* title);


    friend void Application::setWindow(Window *w);
    friend bool Application::run();

    int32_t width() const;
    int32_t height() const;
    std::string& title() const;
    int32_t create();

    void close();
    bool isOpened() const;
    bool isShouldClose() const;
    bool isCreated() const;

    void setCursorDisabled(bool v);
    bool isCursorDisabled() const;
private:
    GLFWwindow* _window = nullptr;
    int32_t _width = 0;
    int32_t _height = 0;
    std::string _title;
    bool opened = false;
    void makeContextCurrent();
    void swapBuffers();

    bool _cursorDisabled = false;

};

#endif // WINDOW_H
