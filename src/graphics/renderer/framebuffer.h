#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstdint>
#include <GL/glew.h>
class Framebuffer
{
public:
    Framebuffer();
    ~Framebuffer();

    void create();
    void deleteFrameBuffer();
    void bind() const;
    void unbind() const;

    bool isComplete() const;


    uint32_t id = 0;

};

#endif // FRAMEBUFFER_H
