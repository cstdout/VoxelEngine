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
