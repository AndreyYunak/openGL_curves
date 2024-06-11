#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &va_ID);
	std::cout << "gen VAO\n";
	Unbind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &va_ID);
	std::cout << "del VAO\n";
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i) 
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset );
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	Unbind();
	vb.Unbind();

}

void VertexArray::Bind() const
{
	glBindVertexArray(va_ID);
	std::cout << "bind VAO\n";
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
	std::cout << "unbind VAO\n";
}
