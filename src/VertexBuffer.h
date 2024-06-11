#pragma once
#include<glad/glad.h> 

class VertexBuffer {
private:
	unsigned int bufferID;
public:
	VertexBuffer(const void* data, unsigned int size, unsigned int type = GL_STATIC_DRAW);
	VertexBuffer();
	~VertexBuffer();

	void VertexBufferData(const void* data, unsigned int size, unsigned int type = GL_STATIC_DRAW);
	void Bind() const;
	void Unbind() const;
};