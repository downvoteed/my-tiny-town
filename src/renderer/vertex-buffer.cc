#include "vertex-buffer.hh"
#include <iostream>
#include "glad/glad.h"

#define GL_CALL(x) \
    do { \
        x; \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) { \
            std::cerr << "OpenGL error " << error << " at " << __FILE__ << ":" << __LINE__ << " - for " << #x << std::endl; \
        } \
    } while (0)

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GL_CALL(glGenBuffers(1, &this->bufferID_));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, this->bufferID_));
	// TODO: be sure about draw type
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::bind() const
{
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, this->bufferID_));
}

void VertexBuffer::unbind() const
{
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer()
{
	GL_CALL(glDeleteBuffers(1, &this->bufferID_));
}
