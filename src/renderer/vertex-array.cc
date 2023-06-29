#include "vertex-array.hh"
#include "vertex-buffer-layout.hh"
#include <iostream>
#include <glad/glad.h>

#define GL_CALL(x) \
    do { \
        x; \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) { \
            std::cerr << "OpenGL error " << error << " at " << __FILE__ << ":" << __LINE__ << " - for " << #x << std::endl; \
        } \
    } while (0)

VertexArray::VertexArray() 
{
   GL_CALL(glGenVertexArrays(1, &this->vaoID_));
}

VertexArray::~VertexArray() 
{
    GL_CALL(glDeleteVertexArrays(1, &this->vaoID_));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    vb.bind();

    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) 
    {
        const auto& element = elements[i];
        GL_CALL(glEnableVertexAttribArray(i));
        GL_CALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }

    vb.unbind();
}

void VertexArray::bind() const 
{
    GL_CALL(glBindVertexArray(this->vaoID_));
}

void VertexArray::unbind() const 
{
    GL_CALL(glBindVertexArray(0));
}
