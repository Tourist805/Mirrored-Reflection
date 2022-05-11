#version 430

layout (location = 0) out vec4 FragColor;
layout(binding=0) uniform sampler2D ProjectorTex;
in vec3 EyeNormal;
in vec4 EyePosition;
in vec4 ProjTexCoord;

uniform struct LightInfo 
{
  vec4 Position; // Light position in eye coords.
  vec3 La;
  vec3 L;// Diffuse light intensity
} Light;

uniform struct MaterialInfo 
{
  vec3 Ka; // Ambent reflectivity
  vec3 Kd;      // Diffuse reflectivity
  vec3 Ks; // Specular reflectivity
  float Shininess;
} Material;

vec3 blinnPhong(vec3 position, vec3 normal)
{
	vec3 ambient = Material.Ka * Light.La;
	vec3 s = normalize(Light.Position.xyz - position);

	float sDotN = max(dot(s, normal), 0);
	vec3 diffuse = Material.Kd * sDotN;
	vec3 specular = vec3(0.0);

	if(sDotN > 0.0)
	{
		vec3 v = normalize(-position.xyz);
		vec3 h = normalize(v + s);
		specular = Material.Ks * pow(max(dot(h, normal), 0.0), Material.Shininess);
	}

	return ambient + Light.L * (diffuse + specular);
}

void main()
{
	vec3 colour = blinnPhong(normalize(EyePosition.xyz), EyeNormal);
	vec3 projTexColour = vec3(0.0);
	if( ProjTexCoord.z > 0.0 )
		projTexColour = textureProj( ProjectorTex, ProjTexCoord ).rgb;

	FragColor = vec4(colour + projTexColour * 0.5, 1);
}