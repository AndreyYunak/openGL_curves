#include "IndexBuffer.h"


IndexBuffer::IndexBuffer(const void* data, unsigned int count_of_index, unsigned int type)
	: count(count_of_index)
{
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count_of_index * sizeof(unsigned int), data, type);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	Unbind();
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &bufferID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
