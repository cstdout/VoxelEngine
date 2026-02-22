#include <iostream>
#include "renderer.h"

Renderer::Renderer(int32_t viewportWidth, int32_t viewportHeight)
{
    if(viewportSizeValid(viewportWidth, viewportHeight))
    {
        _viewportWidth = viewportWidth;
        _viewportHeight = viewportHeight;
    }
}
bool Renderer::viewportSizeValid(int32_t viewportWidth, int32_t viewportHeight) const
{
    return (viewportWidth > 0) && (viewportHeight > 0);
}
bool Renderer::viewportSizeValid() const
{
    return viewportSizeValid(_viewportWidth, _viewportHeight);
}
Renderer::~Renderer()
{
}
void Renderer::render(float delta, int32_t w, int32_t h)
{
    glBindVertexArray(VAO.id);
    if(_offScreenRenderingMode)
    {
        FBO.bind();
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    onDraw(delta, w, h);
    FBO.unbind();
    glBindVertexArray(0);
}
bool Renderer::isInitialized() const
{
    return _initialized;
}
void Renderer::onDraw(float delta, int32_t w, int32_t h)
{
}
void Renderer::init()
{
    VAO.create();
    _initialized = true;
}
void Renderer::initFramebufferOutputTexture(int32_t texWidth, int32_t texHeight)
{
    if(FBO.id > 0)
    {
        framebufferOutput.create(texWidth, texHeight);
        framebufferOutput.setTextureMinMaxFilters(GL_LINEAR, GL_LINEAR);
        framebufferOutput.attachFramebuffer(FBO.id);

    }
    else
    {
        std::cerr << "Renderer::initFramebufferOutputTexture FBO was not created" << std::endl;
    }

}
void Renderer::setOffScreenRendering(bool mode)
{
    _offScreenRenderingMode = mode;
}
bool Renderer::isOffScreenRenderingModeOn() const
{
    return _offScreenRenderingMode;
}
