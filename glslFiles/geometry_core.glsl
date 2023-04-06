#version 440

layout(triangles) in;
layout(triangle_strip, max_vertices=78) out;

in vData
{
 vec3 vs_position;
 vec3 vs_color;
 vec2 vs_texcoord;
 vec3 vs_normal;
} vertices[];

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

out fData
{
 vec3 vs_position;
 vec3 vs_color;
 vec2 vs_texcoord;
 vec3 vs_normal;

}frag;


void main()
{	
  int i;
  for(i = 0; i < gl_in.length(); i++)
  {
	frag.vs_color = vertices[i].vs_color;
	frag.vs_position = vertices[i].vs_position;
	frag.vs_texcoord = vertices[i].vs_texcoord;
	frag.vs_normal = vertices[i].vs_normal;
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vertices[i].vs_position, 1.f);
	EmitVertex();
  }
}  
