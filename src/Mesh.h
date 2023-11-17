#if 0
#pragma once

#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h> // holds all OpenGL type declarations
#include <vector>
#include <string>
#include "Renderer/ShaderProgram.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};


struct Texture {
	unsigned int id;
	std::string type;
	std::string path;  // we store the path of the texture to compare with other textures
};


class Mesh {
public:
	// mesh data
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture>      textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader& shader);
private:
	//  render data
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};
#endif