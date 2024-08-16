#version 330 core

in vec4 vertexColor;
in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D tex0;

void main()
{
   FragColor = texture(tex0, texCoords);
}