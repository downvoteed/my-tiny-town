#include "vertex-array.hh"
#include "vertex-buffer-layout.hh"
#include <glad/glad.h>

VertexArray::VertexArray() 
{
    glGenVertexArrays(1, &this->vaoID_);
}

VertexArray::~VertexArray() 
{
    glDeleteVertexArrays(1, &this->vaoID_);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    bind();
    vb.bind();

    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind() const {
    glBindVertexArray(this->vaoID_);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}
