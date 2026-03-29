#ifndef CHUNKRENDERER_H
#define CHUNKRENDERER_H

#include "src/graphics/renderer/meshrenderer.h"
#include "src/graphics/texture.h"
class ChunkRenderer : public MeshRenderer
{
public:
    ChunkRenderer(const Mesh* mesh, int32_t viewportWidth = 0, int32_t viewportHeight = 0);
    ~ChunkRenderer();
    void setTextureAtlas(Texture* atlas)
    {
        _textureAtlas = atlas;
    }
    void init();

protected:
    Texture* _textureAtlas = nullptr;
    uint32_t _texCoordBuffer = 0;
    void initTextureCoords(int32_t texCoordsBufferInputLocation = 1);
    void linkUniforms();
    void onDraw(float delta, int32_t w, int32_t h);

};

#endif // CHUNKRENDERER_H
