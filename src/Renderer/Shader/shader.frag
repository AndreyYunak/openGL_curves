#version 400

out vec4 frag_color;

in vec2 TexCoords;

uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);

uniform sampler2D mytexture;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main() 
{
	
	frag_color = texture(mytexture, TexCoords);
};