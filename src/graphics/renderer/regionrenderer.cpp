#include "regionrenderer.h"

RegionRenderer::RegionRenderer(const Mesh* mesh, int32_t viewportWidth, int32_t viewportHeight) : MeshRenderer (mesh, viewportWidth, viewportHeight)
{
}
RegionRenderer::~RegionRenderer()
{
    if(_texCoordBuffer)
    {
        glDeleteBuffers(1, &_texCoordBuffer);
    }
    _textureAtlas = nullptr;
}
void RegionRenderer::bindChunkData(uint32_t chunkId)
{
    Mesh* mesh = _chunks[chunkId];

    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh->size * sizeof(float), mesh->vertices, GL_STATIC_DRAW);


    glEnableVertexAttribArray(_shader->getAttribLocation("aPos"));
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glVertexAttribPointer(_shader->getAttribLocation("aPos"), 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, _texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh->uvSize * sizeof(float), mesh->uvs, GL_STATIC_DRAW);

    glEnableVertexAttribArray(_shader->getAttribLocation("aTexCoord"));
    glBindBuffer(GL_ARRAY_BUFFER, _texCoordBuffer);
    glVertexAttribPointer(_shader->getAttribLocation("aTexCoord"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indexCount * sizeof(uint32_t),  mesh->indices , GL_STATIC_DRAW);
    _indexCount = mesh->indexCount;
}
void RegionRenderer::init()
{
    if(_textureAtlas != nullptr)
    {
        _textureAtlas->load();
    }
    if(_shader == nullptr)
    {
        _shader = new Shader(DEFAULT_VERTEX_SHADER, DEFAULT_TEXTURE_FRAGMENT_SHADER);
        shouldDeleteShaderInDestructor = true;
    }
    bool shaderIsValid = (_shader && _shader->compile() && _shader->isValid());
    bool textureIsValid = (_textureAtlas && _textureAtlas->isInitialized());
    if(_chunks != nullptr && shaderIsValid && textureIsValid)
    {
        VAO.create();
        VAO.bind();
        if (_offScreenRenderingMode)
        {
            FBO.create();
            initFramebufferOutputTexture(_viewportWidth, _viewportHeight);
        }


        glEnable(GL_DEPTH_TEST);
        if(_backFaceCulling)
        {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        }


        glGenBuffers(1, &_vertexBuffer);
        glGenBuffers(1, &_texCoordBuffer);
        glGenBuffers(1, &_indexBuffer);

        initUniformMatrices();
        initModel();
        initCamera();

        _camera.Speed = 20.0f;
        _camera.Position = Vec3(128, 10, 128);
        _initialized = true;
    }
}
void RegionRenderer::linkUniforms()
{
    _shader->setUniformMatrix4fv("model", _model.valuePtr());
    _shader->setUniform1i("ourTexture", _textureAtlas->getActiveSlot());
}
void RegionRenderer::onDraw(float delta, int32_t w, int32_t h)
{
    _shader->use();
    _textureAtlas->bind();
    handleEvents(delta);

    _camera.updateViewMatrix();

    glBindBuffer(GL_UNIFORM_BUFFER, _uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, Mat4::sizeInBytes, Mat4::sizeInBytes, _viewMatrix.valuePtr());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    linkUniforms();

    uint32_t chunkId = 0;
    while(chunkId < _chunkCount)
    {
        bindChunkData(chunkId++);

        if(_indexBuffer > 0)
        {
            glDrawElements(_drawMode, _indexCount, GL_UNSIGNED_INT, nullptr);
        }
        else
        {
            glDrawArrays(_drawMode, 0, _vertexCount);
        }
    }
}
