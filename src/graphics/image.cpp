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
uint32_t Image::setPixelColor(uint32_t x, uint32_t y, uint8_t color)
{
    uint32_t idx = index(x, y);
    if(idx <= (_size - _channels))
    {
        bytes[idx] = color;
        bytes[idx + 1] = color;
        bytes[idx + 2] = color;
    }
    return idx;
}
uint32_t Image::setPixelColor(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t idx = index(x, y);
    if(idx <= (_size - _channels))
    {
        bytes[idx] = r;
        bytes[idx + 1] = g;
        bytes[idx + 2] = b;
    }
    return idx;
}
uint32_t Image::setPixelColor(uint32_t x, uint32_t y, const Color& color)
{
    uint32_t idx = index(x, y);
    if(idx <= (_size - _channels))
    {
        bytes[idx] = color.r;
        bytes[idx + 1] = color.g;
        bytes[idx + 2] = color.b;
    }
    return idx;
}
void Image::setAlpha(uint8_t alpha)
{
    uint32_t s = size();
    for(uint32_t i = 3; i < s; i *= 3)
    {
        bytes[i] = alpha;
    }
}
bool Image::save(const std::string& fileName,
                 uint8_t* bytes,
                 uint32_t width,
                 uint32_t height,
                 uint32_t channels,
                 Image::IMG_FORMATS format)
{
    bool res = false;
    switch(format)
    {
        case Image::IMG_FORMATS::PNG:
            res = stbi_write_png(fileName.c_str(),
                                 int(width),
                                 int(height),
                                 int(channels),
                                 bytes,
                                 int(width * channels));
        break;
    }
    return res;
}
uint32_t Image::width() const
{
    return _width;
}
uint32_t Image::height() const
{
    return _height;
}
uint32_t Image::channels() const
{
    return _channels;
}
std::string& Image::path() const
{
    std::string* s = new std::string(_path);
    return *s;
}
Image* Image::fromPath(const std::string& path, bool flipVerticallyOnLoad)
{
    int32_t width, height, channels;
    if(flipVerticallyOnLoad)
    {
        stbi_set_flip_vertically_on_load(1);
    }

    uint8_t* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!data)
    {
        std::cout << "Failed to load image" << std::endl;
        return nullptr;
    }
    Image* image = new Image();
    image->_width = uint32_t(width);
    image->_height = uint32_t(height);
    image->_channels = uint32_t(channels);
    image->_path = path;
    image->bytes = data;
    return image;
}
