#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform Sampler2D sampler2d;

int main()
{
	FragColor = texture(sampler2d, TexCoords);
}