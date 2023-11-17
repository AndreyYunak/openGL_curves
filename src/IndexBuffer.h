#pragma once
#include<glad/glad.h> /*??????????*/

class IndexBuffer {
private:
	unsigned int bufferID;
	unsigned int count;
public:
	IndexBuffer(const void* data, unsigned int count_of_index, unsigned int type = GL_STATIC_DRAW);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

//inline ??????
	inline unsigned int GetCount() const { return count;}
};