#version 460   

layout (location = 0) in vec3 vertex_position;

layout (location = 1) in vec3 aNormal_;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 Tangent_;
layout (location = 4) in vec3 Bitangent_;
layout (location = 5) in vec4 m_BoneIDs_;
layout (location = 6) in vec4 m_Weights_;

out vec2 TexCoords;
out vec3 aNormal;

out vec3 Tangent;
out vec3 Bitangent;
out vec4 m_BoneIDs;
out vec4 m_Weights;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() 
{
	TexCoords = aTexCoords; 
	gl_Position =projection * view * model * vec4(vertex_position, 1.0f);
	
};