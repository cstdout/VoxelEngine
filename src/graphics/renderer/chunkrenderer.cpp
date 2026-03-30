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
void ChunkRenderer::init()
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
    if(_mesh != nullptr && _mesh->verticesExist() && shaderIsValid && textureIsValid)
    {
        VAO.create();
        VAO.bind();
        if (_offScreenRenderingMode)
        {
            FBO.create();
            initFramebufferOutputTexture(_viewportWidth, _viewportHeight);
        }


        glEnable(GL_DEPTH_TEST);

        _vertexCount = _mesh->size;

        initVertexBuffer(_shader->getAttribLocation("aPos"));
        if(_mesh->uvsExist())
        {
            initTextureCoords(_shader->getAttribLocation("aTexCoord"));
        }

        initUniformMatrices();
        initModel();
        initCamera();
        if(_mesh->indicesExist())
        {
            _indexCount = _mesh->indexCount;
            initIndexBuffer();
        }

        _camera.Speed = 20.0f;
        _camera.Position = Vec3(128, 10, 128);
        _initialized = true;
    }
}
void ChunkRenderer::linkUniforms()
{
    _shader->setUniformMatrix4fv("model", _model.valuePtr());
    _shader->setUniform1i("ourTexture", _textureAtlas->getActiveSlot());
}
void ChunkRenderer::onDraw(float delta, int32_t w, int32_t h)
{
    _shader->use();
    _textureAtlas->bind();
    handleEvents(delta);

    _camera.updateViewMatrix();

    glBindBuffer(GL_UNIFORM_BUFFER, _uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, Mat4::sizeInBytes, Mat4::sizeInBytes, _viewMatrix.valuePtr());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    linkUniforms();

    if(_indexBuffer > 0)
    {
        glDrawElements(_drawMode, _indexCount, GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        glDrawArrays(_drawMode, 0, _vertexCount);
    }
}
