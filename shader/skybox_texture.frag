#version 430

layout (location = 0) out vec4 FragColor;
layout (binding = 1) uniform samplerCube SkyBoxTex;

in vec3 Position;

void main()
{
	vec3 texColour = texture(SkyBoxTex, normalize(Position)).rbg;
	texColour = pow(texColour, vec3(1.0 / 2.2));
	FragColor = vec4(texColour, 1.0);
}