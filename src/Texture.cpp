#if 0
#include "Texture.h"
#include <filesystem>
#include <iostream>
#include "Renderer/stb_image.h"

Texture::Texture(std::string path)
{
	
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width = 0, height = 0, nrChannels = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(path.c_str(), &width, &height, &nrChannels, 4);
	if (image)
	{
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "load texture: OK!" << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, ID);

}

unsigned Texture::getID() const
{
	return ID;
}

#endif