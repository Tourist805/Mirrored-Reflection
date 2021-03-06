#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 EyeNormal;
out vec4 EyePosition;
out vec4 ProjTexCoord;

uniform mat4 ProjectorMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;

uniform mat4 MVP;


void main() 
{
	vec4 position = vec4(VertexPosition, 1.0);
	EyeNormal = normalize(NormalMatrix * VertexNormal);
	EyePosition = ModelViewMatrix * position;
	ProjTexCoord = ProjectorMatrix * (ModelMatrix * position);

	gl_Position = MVP * vec4(VertexPosition,1.0);
}