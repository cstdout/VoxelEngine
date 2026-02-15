#include "texture.h"
#include <iostream>
Texture::Texture(uint32_t id, int32_t width, int32_t height, int32_t channels) : _id(id), _width(width), _height(height), _channels(channels)
{
}
Texture::Texture()
{
    _id = 0;
    _width = 0;
    _height = 0;
    _channels = 0;
    _activeSlot = 0;
}
Texture::Texture(const Image* image)
{
    _image = image;
}
Texture::Texture(const Image* image, const TextureConfig& config)
{
    _image = image;
    _config = config;
}
void Texture::copyTexture(const Texture &other)
{
    _id = other._id;
    _width = other._width;
    _height = other._height;
    _channels = other._channels;
    _activeSlot = other._activeSlot;
}
void Texture::operator=(const Texture &other)
{
    copyTexture(other);
}
void Texture::bind(uint32_t slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, _id);
    _activeSlot = slot;
}
void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
Texture* Texture::fromImage(const Image* const image,
                            GLint minFilter,
                            GLint maxFilter,
                            GLint wrapS,
                            GLint wrapT)
{
    Texture* texture = new Texture();
    if(!loadTexture(image, texture, minFilter, maxFilter, wrapS, wrapT))
    {
        delete texture;
        return nullptr;
    }
    return texture;
}
Texture* Texture::fromPath(const std::string& filename, GLint minFilter, GLint maxFilter, GLint wrapS, GLint wrapT)
{
    return fromPath(filename.c_str(), minFilter, maxFilter, wrapS, wrapT);
}
Texture* Texture::fromPath(const char* filename, GLint minFilter, GLint maxFilter, GLint wrapS, GLint wrapT)
{
    Image* img = Image::fromPath(filename);

    if (!img)
    {
        std::cout << "Failed to load texture" << std::endl;
        return nullptr;
    }
    Texture* t = fromImage(img, minFilter, maxFilter, wrapS, wrapT);
//    stbi_image_free(data);
    delete img;
    return t;
}
uint32_t Texture::getActiveSlot() const
{
    return _activeSlot;
}
int32_t Texture::width() const
{
    return _width;
}
int32_t Texture::height() const
{
    return _height;
}
int32_t Texture::channels() const
{
    return _channels;
}
bool Texture::loadTexture(const Image* srcImage,
                          Texture* dst,
                          GLint minFilter,
                          GLint maxFilter,
                          GLint wrapS,
                          GLint wrapT)
{
    if(srcImage == nullptr)
    {
        return false;
    }

    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

    GLint internalFormat = GL_RGB8;
    GLenum format = GL_RGB;

    if(srcImage->channels() == 4)
    {
        internalFormat = GL_RGBA;
        format = GL_RGBA;
    }


    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 internalFormat,
                 srcImage->width(),
                 srcImage->height(),
                 0,
                 format,
                 GL_UNSIGNED_BYTE,
                 srcImage->bytes);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    dst->_id = id;
    dst->_width = srcImage->width();
    dst->_height = srcImage->height();
    dst->_channels = srcImage->channels();
    return true;

}
bool Texture::load()
{
    if(_image == nullptr)
    {
        return false;
    }
    return loadTexture(_image,
                       this,
                       _config.minFilter,
                       _config.maxFilter,
                       _config.wrapS,
                       _config.wrapT);
}
