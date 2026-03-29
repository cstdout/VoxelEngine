#include "chunkrenderer.h"

ChunkRenderer::ChunkRenderer()
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
