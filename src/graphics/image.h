#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <string>

struct Color
{
    Color(uint8_t r, uint8_t g, uint8_t b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Image
{
public:
    enum IMG_FORMATS {
      PNG,
      JPG
    };
    Image();
    Image(uint32_t width, uint32_t height, uint32_t channels);
    Image(const Image& other);
    ~Image();

    static Image* fromPath(const std::string& path, bool flipVerticallyOnLoad = false);

    uint32_t width() const;
    uint32_t height() const;
    uint32_t channels() const;
    std::string& path() const;
    uint32_t size() const;
    uint32_t setPixelColor(uint32_t x, uint32_t y, uint8_t color);
    uint32_t setPixelColor(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
    uint32_t setPixelColor(uint32_t x, uint32_t y, const Color& color);
    void setAlpha(uint8_t alpha);
    uint8_t* bytes = nullptr;
    bool save(const std::string& fileName, Image::IMG_FORMATS format, bool updatePathOnSuccess = false);

    static bool save(const std::string& fileName,
                     uint8_t* bytes,
                     uint32_t width,
                     uint32_t height,
                     uint32_t channels,
                     Image::IMG_FORMATS format);

    bool addImage(const Image& other, uint32_t x = 0, uint32_t y = 0);
    uint32_t index(uint32_t x, uint32_t y, uint32_t stride = 0) const;
private:
    uint32_t _width = 0;
    uint32_t _height = 0;
    uint32_t _channels = 4;
    uint32_t _size = 0;
    std::string _path;

};

#endif // IMAGE_H
