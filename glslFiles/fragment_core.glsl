#version 440

struct Material
{
//color and intensity
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
//textures
	sampler2D water;
	sampler2D sand;
	sampler2D dirt;
	sampler2D grass;
	sampler2D hill;
	sampler2D mountain;
	sampler2D snow;
};

in fData
{
 vec3 vs_position;
 vec3 vs_color;
 vec2 vs_texcoord;
 vec3 vs_normal;

}frag;

out vec4 fs_color;

//Uniforms
uniform vec3 camPosition;
uniform vec3 lightPos0;
uniform Material material;
uniform bool tex;
uniform int viewMode;

//Functions
//vec3 calculateAmbient(Material material)
//{
//	return material.ambient;
//}
//
//vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0)
//{
//	vec3 posToLightDirVec = normalize(lightPos0 - vs_position);
//	float diffuse = clamp(dot(posToLightDirVec, vs_normal),0 ,1);
//
//	vec3 diffuseFinal = material.diffuse * diffuse;
//
//	return diffuseFinal;
//}
//
//vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0, vec3 camPosition)
//{
//	vec3 lightToPosDirVec = normalize(vs_position - lightPos0);
//	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
//	vec3 posToViewDirVec = normalize(camPosition - vs_position);
//	float specular = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);
//
//	vec3 specularFinal = material.specular * specular;
//
//	return specularFinal;
//}



void main()
{
	////ambient light
	//vec3 ambientFinal = calculateAmbient(material);

	////difuse light
	//vec3 diffuseFinal = calculateDiffuse(material, frag.vs_position, frag.vs_normal, lightPos0);

	////specular light
	//vec3 specularFinal = calculateSpecular(material, frag.vs_position, frag.vs_normal, lightPos0, camPosition);

	if (viewMode == 1)
	{
		if (frag.vs_position.y >= -8.0f && frag.vs_position.y <= -4.5f)
		{
			fs_color = texture(material.water, frag.vs_texcoord);
		}
		else if (frag.vs_position.y > -4.5f && frag.vs_position.y <= -3.9f)
		{

			vec3 water = texture(material.water, frag.vs_texcoord).rgb;
			vec3 sand = texture(material.sand, frag.vs_texcoord).rgb;
			float a = smoothstep(-4.5f, -3.9f, frag.vs_position.y);
			vec3 final_texture = mix(water, sand, a);
			fs_color = vec4(final_texture, 0.1f);

		}
		else if (frag.vs_position.y > -3.9f && frag.vs_position.y <= -2.f)
		{

			vec3 sand = texture(material.sand, frag.vs_texcoord).rgb;
			vec3 dirt = texture(material.dirt, frag.vs_texcoord).rgb;
			float a = smoothstep(-3.9f, -2.f, frag.vs_position.y);
			vec3 final_texture = mix(sand, dirt, a);
			fs_color = vec4(final_texture, 0.1f);

		}
		else if (frag.vs_position.y > -2.f && frag.vs_position.y <= 0.f)
		{

			vec3 dirt = texture(material.dirt, frag.vs_texcoord).rgb;
			vec3 grass = texture(material.grass, frag.vs_texcoord).rgb;
			float a = smoothstep(-2.f, 0.f, frag.vs_position.y);
			vec3 final_texture = mix(dirt, grass, a);
			fs_color = vec4(final_texture, 0.1f);

		}
		else if (frag.vs_position.y > 0.f && frag.vs_position.y <= 1.f)
		{
			//fs_color = texture(material.hill, frag.vs_texcoord);

			vec3 grass = texture(material.grass, frag.vs_texcoord).rgb;
			vec3 hill = texture(material.hill, frag.vs_texcoord).rgb;
			float a = smoothstep(0.f, 1.f, frag.vs_position.y);
			vec3 final_texture = mix(grass, hill, a);
			fs_color = vec4(final_texture, 0.1f);

		}
		else if (frag.vs_position.y > 1.f && frag.vs_position.y <= 7.f)
		{
			//fs_color = texture(material.mountain, frag.vs_texcoord);

			vec3 hill = texture(material.hill, frag.vs_texcoord).rgb;
			vec3 mountain = texture(material.mountain, frag.vs_texcoord).rgb;
			float a = smoothstep(0.5f, 7.f, frag.vs_position.y);
			vec3 final_texture = mix(hill, mountain, a);
			fs_color = vec4(final_texture, 0.1f);

		}
		else if (frag.vs_position.y > 7.f && frag.vs_position.y <= 10.f)
		{
			vec3 mountain = texture(material.mountain, frag.vs_texcoord).rgb;
			vec3 snow = texture(material.snow, frag.vs_texcoord).rgb;
			float a = smoothstep(7.f, 10.f, frag.vs_position.y);
			vec3 final_texture = mix(mountain, snow, a);
			fs_color = vec4(final_texture, 0.1f);
		}
		else if (frag.vs_position.y > 10.f)
		{
			fs_color = texture(material.snow, frag.vs_texcoord);
		}
	}
	else
	{
		fs_color = vec4(frag.vs_color, 1.f);
	}
}