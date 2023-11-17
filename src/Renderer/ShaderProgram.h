#ifndef SHARED_H
#define SHARED_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
//#include <gl/glew.h>   //????????


#include <glad/glad.h>
#include <GLFW/glfw3.h>

class  Shader
{
private:

public:
	GLuint Program; //???????


	Shader(const GLchar* vareteh_path, const GLchar* fragment_path);
	~Shader();

	void Use();
	void setInt(const std::string& name, int value) const;

};


#endif