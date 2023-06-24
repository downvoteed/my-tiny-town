#include "index-buffer.hh"
#include "glad/glad.h"	

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : count_(count) {
    glGenBuffers(1, &this->indexBufferID_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferID_);
    // TODO : check if GL_STATIC_DRAW is the right usage
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() 
{
    glDeleteBuffers(1, &this->indexBufferID_);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferID_);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
