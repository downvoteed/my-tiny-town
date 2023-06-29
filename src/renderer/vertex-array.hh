#pragma once
#include "vertex-buffer.hh"
#include "vertex-buffer-layout.hh"

/**
 * @brief Class to abstract Vertex Array Object (VAO) in OpenGL
 */
class VertexArray 
{
public:
    /**
	 * @brief Construct a new Vertex Array object
	 */
    VertexArray();
    ~VertexArray();
	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;
	VertexArray(VertexArray&&) = delete;
	VertexArray& operator=(VertexArray&&) = delete;

    /**
    * @brief Add a Vertex Buffer to the Vertex Array
    * @param vb Vertex Buffer to add
    * @param layout Layout of the Vertex Buffer
	*/
    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    /**  
	* @brief Bind the Vertex Array
    */
    void bind() const;
    /**
    * @brief Unbind the Vertex Array
    */
    void unbind() const;

private:
    unsigned int vaoID_;
};
