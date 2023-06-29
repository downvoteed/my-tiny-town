#include "index-buffer.hh"
#include "glad/glad.h"	
#include <iostream>

#define GL_CALL(x) \
    do { \
        x; \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) { \
            std::cerr << "OpenGL error " << error << " at " << __FILE__ << ":" << __LINE__ << " - for " << #x << std::endl; \
        } \
    } while (0)

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : count_(count) {
    GL_CALL(glGenBuffers(1, &this->indexBufferID_));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferID_));
    // TODO : check if GL_STATIC_DRAW is the right usage
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() 
{
    GL_CALL(glDeleteBuffers(1, &this->indexBufferID_));
}

void IndexBuffer::bind() const
{
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferID_));
}

void IndexBuffer::unbind() const
{
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
