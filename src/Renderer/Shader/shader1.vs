#version 400   

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 aTexCoords;


out vec2 TexCoords;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() 
{
	TexCoords = aTexCoords; 
	gl_Position =projection * view * model * vec4(vertex_position, 1.0f);
	
};