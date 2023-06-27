#pragma once
#include <glad/glad.h>

class FrameBuffer 
{
public:
    FrameBuffer();
    ~FrameBuffer();

    void bind() const;
    void unbind() const;

    GLuint getTexture() const;

private:
    GLuint fbo_;
    GLuint texture_;
};