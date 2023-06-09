#version 440

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec2 vertex_texcoord;
layout(location = 3) in vec3 vertex_normal;


out vData
{
 vec3 vs_position;
 vec3 vs_color;
 vec2 vs_texcoord;
 vec3 vs_normal;

}vertex;


uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
	vertex.vs_position = vec4(ModelMatrix * vec4(vertex_position, 1.f)).xyz;
	vertex.vs_color = vertex_color;
	vertex.vs_texcoord = vec2(vertex_texcoord.x, vertex_texcoord.y * -1.f);
	vertex.vs_normal = mat3(ModelMatrix) * vertex_normal;

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vertex_position, 1.f);
}