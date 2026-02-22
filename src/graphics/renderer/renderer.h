#ifndef RENDERER_H
#define RENDERER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "src/graphics/texture.h"
#include "src/graphics/renderer/vertexattributeobject.h"
#include "src/graphics/renderer/framebuffer.h"


class Renderer
{
public:
    Renderer(int32_t viewportWidth = 0, int32_t viewportHeight = 0);
    ~Renderer();

    VertexAttributeObject VAO;
    Framebuffer FBO;

    void initFramebufferOutputTexture(int32_t texWidth, int32_t texHeight);

    void render(float delta = 0.0f, int32_t w = 0, int32_t h = 0);

    virtual void init();
    bool isInitialized() const;

    Texture framebufferOutput;

    void setOffScreenRendering(bool mode);
    bool isOffScreenRenderingModeOn() const;
protected:

    virtual void onDraw(float delta = 0.0f, int32_t w = 0, int32_t h = 0);
    int32_t _viewportWidth = 0;
    int32_t _viewportHeight = 0;


    bool viewportSizeValid() const;
    bool viewportSizeValid(int32_t viewportWidth, int32_t viewportHeight) const;
    bool _initialized = false;
    bool _offScreenRenderingMode = false;


};

#endif // RENDERER_H
