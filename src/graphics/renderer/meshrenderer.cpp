#include <iostream>
#include "meshrenderer.h"

MeshRenderer::MeshRenderer(const Mesh* mesh, int32_t viewportWidth, int32_t viewportHeight)
{
    _viewportWidth = viewportWidth;
    _viewportHeight = viewportHeight;
    _mesh = mesh;
}
MeshRenderer::~MeshRenderer()
{
    if(_vertexBuffer)
    {
        glDeleteBuffers(1, &_vertexBuffer);
    }
    if(_indexBuffer)
    {
        glDeleteBuffers(1, &_indexBuffer);
    }
}
void MeshRenderer::setShader(Shader *shader)
{
    _shader = shader;
}
