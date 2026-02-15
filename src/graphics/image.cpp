#include <iostream>
#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

Image::Image()
{
}
Image::Image(const Image& other)
{
    bytes = other.bytes;
    _width = other._width;
    _height = other._height;
    _channels = other._channels;
    _path = other._path;

    _size = other._size;
}
Image::Image(uint32_t width, uint32_t height, uint32_t channels)
{
    _width = width;
    _height = height;
    _channels = channels;
    uint32_t s = width * height * channels;
    _size = s;
    bytes = new uint8_t[s];
    std::fill_n(bytes, s, 0);
}
Image::~Image()
{
    if(bytes != nullptr)
    {
        stbi_image_free(bytes);
    }
}
uint32_t Image::size() const
{
    return _size;
}
