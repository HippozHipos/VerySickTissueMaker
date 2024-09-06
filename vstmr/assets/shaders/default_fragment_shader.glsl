#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightColor;
uniform vec3 materialColor;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightPos = vec3( 0.0f, 20, 5 );
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 result = (ambient + diffuse) * materialColor;//(ambient + diffuse) * materialColor;
	FragColor = vec4(result, 1.0);
}