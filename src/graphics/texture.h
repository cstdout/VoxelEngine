#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "image.h"

struct TextureConfig
{
    GLint minFilter = GL_LINEAR;
    GLint maxFilter = GL_LINEAR;
    GLint wrapS = GL_CLAMP_TO_EDGE;
    GLint wrapT = GL_CLAMP_TO_EDGE;

    void operator=(const TextureConfig& other)
    {
        minFilter = other.minFilter;
        maxFilter = other.maxFilter;
        wrapS = other.wrapS;
        wrapT = other.wrapT;
    }

};

class Texture
{
public:
    Texture();
    Texture(const Image* const image);
    Texture(const Image* const image, const TextureConfig& config);
    bool load();

    Texture(const Texture& other);
    ~Texture();

    void bind(uint32_t slot = 0);
    void unbind() const;
    static Texture* fromImage(const Image* image,
                              GLint minFilter = GL_LINEAR,
                              GLint maxFilter = GL_LINEAR,
                              GLint wrapS = GL_CLAMP_TO_EDGE,
                              GLint wrapT = GL_CLAMP_TO_EDGE);
    static Texture * fromPath(const std::string& filename,
                               GLint minFilter = GL_LINEAR,
                               GLint maxFilter = GL_LINEAR,
                               GLint wrapS = GL_CLAMP_TO_EDGE,
                               GLint wrapT = GL_CLAMP_TO_EDGE);
    static Texture * fromPath(const char* filename,
                               GLint minFilter = GL_LINEAR,
                               GLint maxFilter = GL_LINEAR,
                               GLint wrapS = GL_CLAMP_TO_EDGE,
                               GLint wrapT = GL_CLAMP_TO_EDGE);
    uint32_t getActiveSlot() const;
    void operator=(const Texture& other);
    bool isInitialized() const;

    int32_t width() const;
    int32_t height() const;
    int32_t channels() const;


    void create(int32_t width, int32_t height, int32_t channels = 3);
    void setTextureMinMaxFilters(GLint minFilter = GL_LINEAR,
                                 GLint maxFilter = GL_LINEAR);
    void attachFramebuffer(uint32_t fboId);
    void detachFramebuffer();

    uint32_t attachedFbo() const;
    uint32_t id() const;
private:
    Texture(uint32_t id, int32_t width, int32_t height, int32_t channels);
    uint32_t _id;
    int32_t _width;
    int32_t _height;
    uint32_t _activeSlot;
    int32_t _channels;
    void copyTexture(const Texture& other);
    static bool loadTexture(const Image* srcImage,
                            Texture* dst,
                            GLint minFilter = GL_LINEAR,
                            GLint maxFilter = GL_LINEAR,
                            GLint wrapS = GL_CLAMP_TO_EDGE,
                            GLint wrapT = GL_CLAMP_TO_EDGE);
    const Image* _image = nullptr;

    TextureConfig _config;


    uint32_t _fboId = 0;
};


#endif // TEXTURE_H
