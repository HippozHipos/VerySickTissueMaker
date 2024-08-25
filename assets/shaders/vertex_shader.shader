#version 330 core

layout (location = 0) in vec3 aPos;
//layout(location = 1) in vec4 aColor;
//layout(location = 2) in vec2 aTexCoords;

uniform mat4 projection;
uniform mat4 view;
//out vec4 vertexColor;
//out vec2 texCoords;

void main()
{
	gl_Position = projection * view * vec4(aPos, 1.0);
	//vertexColor = aColor;
	//texCoords = aTexCoords;
}