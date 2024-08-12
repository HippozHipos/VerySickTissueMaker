#version 330 core

layout (location = 0) in vec3 aPos;

uniform float x;
out float xout; 

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   xout = x;
}