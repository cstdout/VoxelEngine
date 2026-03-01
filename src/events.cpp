#include <cstring>
#include "events.h"

bool Events::initialized = false;
uint32_t Events::currentFrame = 0;
double Events::deltaX = 0.0;
double Events::deltaY = 0.0;
double Events::x = 0.0;
double Events::y = 0.0;
bool Events::cursorLocked = false;
bool Events::cursorStarted = false;

bool* Events::keys;
uint32_t* Events::frames;

void Events::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos){
    if (Events::cursorStarted){
        Events::deltaX += xpos - Events::x;
        Events::deltaY += ypos - Events::y;
    }
    else {
        Events::cursorStarted = true;
    }
    Events::x = xpos;
    Events::y = ypos;
}

void Events::mouseButtonCallback(GLFWwindow* window, int32_t button, int32_t action, int32_t mode){
    switch (action) {
        case GLFW_PRESS:
            Events::keys[Events::MOUSE_BUTTONS_POS + button] = true;
            Events::frames[Events::MOUSE_BUTTONS_POS + button] = Events::currentFrame;
        break;
        case GLFW_RELEASE:
            Events::keys[Events::MOUSE_BUTTONS_POS + button] = false;
            Events::frames[Events::MOUSE_BUTTONS_POS + button] = Events::currentFrame;
        break;
    }
}

void Events::keyCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    switch (action) {
        case GLFW_PRESS:
            Events::keys[key] = true;
            Events::frames[key] = Events::currentFrame;
        break;
        case GLFW_RELEASE:
            Events::keys[key] = false;
            Events::frames[key] = Events::currentFrame;
        break;
    }
}
int Events::initialize(){

    Events::keys = new bool[1032];
    Events::frames = new uint32_t[1032];

    memset(Events::keys, false, 1032 * sizeof(bool));
    memset(Events::frames, 0, 1032 * sizeof(uint32_t));
    Events::initialized = true;
    return 0;
}
void Events::setEventCallbacks(GLFWwindow *window)
{
    glfwSetKeyCallback(window, Events::keyCallback);
    glfwSetMouseButtonCallback(window, Events::mouseButtonCallback);
    glfwSetCursorPosCallback(window, Events::cursorPositionCallback);
}
void Events::unsetEventCallbacks(GLFWwindow *window)
{
    glfwSetKeyCallback(window, nullptr);
    glfwSetMouseButtonCallback(window, nullptr);
    glfwSetCursorPosCallback(window, nullptr);
}
void Events::pollEvents() {
    ++(Events::currentFrame);
    Events::deltaX = 0.0;
    Events::deltaY = 0.0;
    glfwPollEvents();
}
bool Events::isInitialized()
{
    return initialized;
}
bool Events::pressed(int32_t keycode) {
    if (keycode < 0 || keycode >= MOUSE_BUTTONS_POS)
        return false;
    return keys[keycode];
}

bool Events::jpressed(int32_t keycode) {
    if (keycode < 0 || keycode >= MOUSE_BUTTONS_POS)
        return false;
    return keys[keycode] && frames[keycode] == currentFrame;
}

bool Events::clicked(int32_t button){
    int index = MOUSE_BUTTONS_POS + button;
    return keys[index];
}

bool Events::jclicked(int32_t button) {
    int index = MOUSE_BUTTONS_POS + button;
    return keys[index] && frames[index] == currentFrame;
}

