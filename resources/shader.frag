#version 330 core

layout(location = 0) out vec4 out_color;


in vec3 normal;

uniform vec3 color;


void main()
{

	vec3 sunLight = normalize(vec3(0.2,1,-0.1));

	float lightColor = clamp(dot(normal, sunLight), 0, 1);
	float ambient = 0.4;

	lightColor += ambient;

	out_color.rgb = vec3(color) * lightColor;
	out_color.a = 1;

}

