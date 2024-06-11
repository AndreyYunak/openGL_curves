#include "VertexBuffer.h"



VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int type)
{
	glGenBuffers(1, &bufferID);
	Bind();
	VertexBufferData(data, size, type);
	Unbind();
}

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &bufferID);	
}

void VertexBuffer::VertexBufferData(const void* data, unsigned int size, unsigned int type) //GL_ARRAY_BUFFER and GL_ELEMENT_ARRAY_BUFFER
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, type);
	Unbind();
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &bufferID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
