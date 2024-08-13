#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 rotation;
uniform mat4 translation;

void main()
{
	gl_Position = projection * translation * rotation * vec4(aPos, 1.0);
}