#version 440

struct Material
{
//color and intensity
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
//textures
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

//Uniforms
uniform vec3 camPosition;
uniform vec3 lightPos0;
uniform Material material;

//Functions
vec3 calculateAmbient(Material material)
{
	return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0)
{
	vec3 posToLightDirVec = normalize(lightPos0 - vs_position);
	float diffuse = clamp(dot(posToLightDirVec, vs_normal),0 ,1);

	vec3 diffuseFinal = material.diffuse * diffuse;

	return diffuseFinal;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0, vec3 camPosition)
{
	vec3 lightToPosDirVec = normalize(vs_position - lightPos0);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(camPosition - vs_position);
	float specular = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);

	vec3 specularFinal = material.specular * specular;

	return specularFinal;
}



void main()
{
	//ambient light
	vec3 ambientFinal = calculateAmbient(material);

	//difuse light
	vec3 diffuseFinal = calculateDiffuse(material, vs_position, vs_normal, lightPos0);

	//specular light
	vec3 specularFinal = calculateSpecular(material, vs_position, vs_normal, lightPos0, camPosition);

	//attenuation 


	//fs_color = texture(material.diffuseTex, vs_texcoord) *
	//(vec4(ambientFinal, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));

	fs_color = vec4(vs_color, 1.f) *
	(vec4(ambientFinal, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));

}