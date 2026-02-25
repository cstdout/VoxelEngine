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
void MeshRenderer::initVertexBuffer(int32_t vertexCoordInputLocation)
{
    glGenBuffers(1, &_vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, _vertexCount * sizeof(float), _mesh->vertices, GL_STATIC_DRAW);


    glEnableVertexAttribArray(vertexCoordInputLocation);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glVertexAttribPointer(vertexCoordInputLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}
