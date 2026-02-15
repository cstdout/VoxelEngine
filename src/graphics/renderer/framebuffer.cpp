#include "framebuffer.h"

Framebuffer::Framebuffer()
{

}
Framebuffer::~Framebuffer()
{
    deleteFrameBuffer();
}
void Framebuffer::create()
{
    glGenFramebuffers(1, &id);
}
bool Framebuffer::isComplete() const
{
    return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
}
void Framebuffer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}
void Framebuffer::unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Framebuffer::deleteFrameBuffer()
{
    if(id > 0)
    {
        glDeleteFramebuffers(1, &id);
        id = 0;
    }
}
