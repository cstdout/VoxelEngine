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
