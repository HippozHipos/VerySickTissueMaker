#version 330 core

out vec4 FragColor;

in float outx;

void main()
{
   FragColor = vec4(outx, 0.5f, 0.2f, 1.0f);
}