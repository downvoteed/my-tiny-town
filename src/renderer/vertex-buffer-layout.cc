#include "vertex-buffer-layout.hh"
#include "vertex-buffer-element.hh"
#include "glad/glad.h"

VertexBufferLayout::VertexBufferLayout()
    : stride_(0) {}

template<>
void VertexBufferLayout::push<float>(unsigned int count) 
{
    this->elements_.push_back({ GL_FLOAT, count, GL_FALSE });
    this->stride_ += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
    this->elements_.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    this->stride_ += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::push<unsigned char>(unsigned int count) 
{
    this->elements_.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    this->stride_ += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}