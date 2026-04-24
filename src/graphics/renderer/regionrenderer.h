#ifndef REGIONRENDERER_H
#define REGIONRENDERER_H



#include "src/graphics/renderer/meshrenderer.h"
#include "src/graphics/texture.h"
class RegionRenderer : public MeshRenderer
{
public:
    RegionRenderer(const Mesh* mesh, int32_t viewportWidth = 0, int32_t viewportHeight = 0);
    ~RegionRenderer();
    void setTextureAtlas(Texture* atlas)
    {
        _textureAtlas = atlas;
    }
    void setRegion(Mesh** region, uint32_t chunkCount)
    {
        _chunks = region;
        _chunkCount = chunkCount;
    }
    void init();
    void setBackFaceCulling(bool flag)
    {
        this->_backFaceCulling = flag;
    }

protected:
    Texture* _textureAtlas = nullptr;
    uint32_t _texCoordBuffer = 0;
    void linkUniforms();
    void onDraw(float delta, int32_t w, int32_t h);

    Mesh** _chunks = nullptr;
    uint32_t _chunkCount = 0;
    void bindChunkData(uint32_t chunkId);
    bool _backFaceCulling = false;
};

#endif // REGIONRENDERER_H
