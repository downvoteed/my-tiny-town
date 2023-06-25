#pragma once
#include <vector>
#include "vertex-buffer-element.hh"


/**
 * @brief Vertex Layout Specification class
 * @see https://www.khronos.org/opengl/wiki/Vertex_Specification_Best_Practices
 */
class VertexBufferLayout
{
public:
    VertexBufferLayout();

    template<typename T>
    void push(unsigned int count);

    inline const std::vector<VertexBufferElement>& getElements() const
    {
        return this->elements_;
    }
    inline unsigned int getStride() const
    { 
        return this->stride_;
    }

private:
    std::vector<VertexBufferElement> elements_;
    // offset
    unsigned int stride_;
};
