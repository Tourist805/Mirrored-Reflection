#version 430

layout (location = 0) in vec3 VertexPosition;

out vec3 Position;

//uniform mat4 ModelViewMatrix;
//uniform mat3 NormalMatrix;
//uniform mat4 ProjectionMatrix;
uniform mat4 MVP;


void main() {

	//Position = (ModelViewMatrix * vec4(VertexPosition,1.0)).xyz;
	Position = VertexPosition;

	gl_Position = MVP * vec4(VertexPosition,1.0);
}