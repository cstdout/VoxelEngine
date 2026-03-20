#include <iostream>
#include "src/application.h"
#include "src/window.h"
#include "src/graphics/renderer/meshrenderer.h"
#include "src/graphics/mesh/block.h"
using namespace std;

int main()
{

    const int32_t WINDOW_WIDTH = 720;
    const int32_t WINDOW_HEIGHT = 680;


    Block block;

    MeshRenderer meshRenderer(&block, WINDOW_WIDTH, WINDOW_HEIGHT);
    Window w(WINDOW_WIDTH, WINDOW_HEIGHT, "My Window");
    w.setCursorDisabled(true);

    Application app;
    app.setWindow(&w);
    app.setRenderer(&meshRenderer);

    app.run();


    return 0;
}
