#pragma once

#include<vector>
#include<glad/glad.h> 

struct VertexBufferElement 
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized = GL_FALSE;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return sizeof(GLfloat);
			case GL_UNSIGNED_INT:	return sizeof(GLuint);
			case GL_UNSIGNED_BYTE:	return sizeof(GLbyte);
		}
		//ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout 
{

private:
	std::vector<VertexBufferElement> v_Elements;
	unsigned int stride;
	unsigned int stride2;

public:
	VertexBufferLayout()
		: stride(0), stride2(0) {};

	template <typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}
	/*
		ADD OTHER!
	*/
	template <>
	void Push<float>(unsigned int count)
	{
		v_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += (count) * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template <>
	void Push<double>(unsigned int count)
	{
		v_Elements.push_back({ GL_DOUBLE, count, GL_FALSE });
		stride += (count)*VertexBufferElement::GetSizeOfType(GL_DOUBLE);
	}

	inline const std::vector<VertexBufferElement> & GetElements() const { return v_Elements; }
	inline unsigned int GetStride() const { return stride; }

	
};