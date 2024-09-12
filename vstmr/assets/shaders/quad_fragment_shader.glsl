#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D sampler2d;

void main()
{
	FragColor = texture(sampler2d, TexCoords);
}