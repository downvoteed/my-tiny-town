#pragma once

class VertexBuffer
{
public:
	// rule of 5
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	VertexBuffer(const VertexBuffer& other) = delete;
	VertexBuffer(VertexBuffer&& other) noexcept = delete;
	VertexBuffer& operator=(const VertexBuffer& other) = delete;

	void bind() const;
	void unbind() const;

private:
	unsigned int bufferID;
};

