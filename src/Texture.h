#if 0
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#define STB_IMAGE_IMPLEMENTATION

#include <string>


class Texture
{
	unsigned int ID;
public:
	Texture::Texture(std::string path);
	unsigned Texture::getID() const;

};
#endif