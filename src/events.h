#ifndef EVENT_H
#define EVENT_H
#include <cstdint>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Events
{
public:

    static int initialize();
    static void pollEvents();

    static bool pressed(int32_t keycode);
    static bool jpressed(int32_t keycode);

    static bool clicked(int32_t button);
    static bool jclicked(int32_t button);

    static void keyCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void mouseButtonCallback(GLFWwindow* window, int32_t button, int32_t action, int32_t mode);

    static void setEventCallbacks(GLFWwindow* window);
    static void unsetEventCallbacks(GLFWwindow* window);
    static bool isInitialized();

    static double deltaX;
    static double deltaY;
    static double x;
    static double y;

private:
    static const int32_t MOUSE_BUTTONS_POS = 1024;
    static bool* keys;
    static uint32_t * frames;
    static uint32_t currentFrame;

    static bool cursorLocked;
    static bool cursorStarted;
    static bool initialized;
};

#endif // EVENT_H
