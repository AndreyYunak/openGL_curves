#ifndef SHARED_H
#define SHARED_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
//#include <gl/glew.h>   //????????
#include <glad/glad.h>

class  Shader
{
public:
	GLuint Program;
	Shader(const GLchar* vareteh_path, const GLchar* fragment_path);
	void Use();
	~Shader();

};




#endif