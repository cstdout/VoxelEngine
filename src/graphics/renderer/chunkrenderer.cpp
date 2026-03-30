#include "chunkrenderer.h"

ChunkRenderer::ChunkRenderer(const Mesh* mesh, int32_t viewportWidth, int32_t viewportHeight) : MeshRenderer (mesh, viewportWidth, viewportHeight)
{
}
ChunkRenderer::~ChunkRenderer()
{
    if(_texCoordBuffer)
    {
        glDeleteBuffers(1, &_texCoordBuffer);
    }
    _textureAtlas = nullptr;
}
void ChunkRenderer::initTextureCoords(int32_t texCoordsBufferInputLocation)
{

    glGenBuffers(1, &_texCoordBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, _texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, _mesh->uvSize * sizeof(float), _mesh->uvs, GL_STATIC_DRAW);

    glEnableVertexAttribArray(texCoordsBufferInputLocation);
    glBindBuffer(GL_ARRAY_BUFFER, _texCoordBuffer);
    glVertexAttribPointer(texCoordsBufferInputLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

}
