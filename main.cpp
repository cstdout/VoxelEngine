#include <iostream>
#include "src/application.h"
#include "src/window.h"
#include "src/graphics/renderer/renderer.h"
using namespace std;

int main()
{

    const int32_t WINDOW_WIDTH = 720;
    const int32_t WINDOW_HEIGHT = 680;

    Renderer renderer;
    Window w(WINDOW_WIDTH, WINDOW_HEIGHT, "My Window");

    Application app;
    app.setWindow(&w);
    app.setRenderer(&renderer);

    app.run();


    return 0;
}
