#version 430
// uniforms from the vertex shader
in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

// Camera position defined in cpp file
uniform vec3 CamPos;

// Diffuse texture that is used as a light source
layout(binding = 0) uniform samplerCube DiffuseLightTex;


uniform struct MaterialInfo
{
	vec3 Colour;
} Material;

layout(location = 0) out vec4 FragColor;

// Formula for approximating the dot product 
// Reducing amount of light that reaches the bottom 
vec3 schlickFresnel(float dotProduct)
{
	vec3 fo = vec3(0.04);
	return fo + (1 - fo) * pow(1.0 - dotProduct, 5);
}

void main()
{
	float gamma = 2.2;
	vec3 n = normalize(Normal);
	vec3 v = normalize(CamPos - Position);

	// Look up from the texture corresponding intensity
	vec3 light = texture(DiffuseLightTex, n).rgb;
	vec3 colour = Material.Colour; 

	// Use gamma correction to make image more blurry
	// Apply linear mapping
	colour = pow(colour, vec3(gamma));

	colour *= light  * colour * (1.0 - schlickFresnel(dot(n, v)));
	//colour = light * colour;

	colour = pow(colour, vec3(1.0 / gamma));

	FragColor = vec4(colour, 1);
}