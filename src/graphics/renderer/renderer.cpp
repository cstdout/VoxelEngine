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
