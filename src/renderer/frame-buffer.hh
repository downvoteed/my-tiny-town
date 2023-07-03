#pragma once
#include <glad/glad.h>

class FrameBuffer 
{
public:
    FrameBuffer() = delete;
    FrameBuffer(bool useDepth);
    ~FrameBuffer();
	FrameBuffer(const FrameBuffer&) = delete;
	FrameBuffer& operator=(const FrameBuffer&) = delete;
	FrameBuffer(FrameBuffer&&) = delete;
    FrameBuffer& operator=(FrameBuffer&&) = delete;

    void bind() const;
    void unbind() const;

    GLuint getTexture() const;

private:
    GLuint fbo_;
    GLuint texture_;
};