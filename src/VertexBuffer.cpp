#include "VertexBuffer.h"



VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int type)
{
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
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
