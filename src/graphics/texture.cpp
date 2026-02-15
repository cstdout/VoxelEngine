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
