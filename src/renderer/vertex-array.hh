#pragma once
#include "vertex-buffer.hh"
#include "vertex-buffer-layout.hh"

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void bind() const;
    void unbind() const;

private:
    unsigned int rendererID;
};
