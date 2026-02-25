#include <iostream>
#include "meshrenderer.h"

MeshRenderer::MeshRenderer(const Mesh* mesh, int32_t viewportWidth, int32_t viewportHeight)
{
    _viewportWidth = viewportWidth;
    _viewportHeight = viewportHeight;
    _mesh = mesh;
}
