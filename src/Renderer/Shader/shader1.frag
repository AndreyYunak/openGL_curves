#version 400

out vec4 frag_color;

in vec2 TexCoords;

uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);

uniform sampler2D mytexture;


void main() 
{
	
	frag_color = texture(mytexture, TexCoords);
};