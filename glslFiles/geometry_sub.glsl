#version 440

layout (triangles) in;
layout (triangle_strip, max_vertices = 112) out;

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec3 vs_position;
out vec3 vs_color;
out vec2 vs_texcoord;
out vec3 vs_normal;

uniform int sub_divisions;
uniform mat4 MVP;

void main()
{
	vec4 v0 = gl_in[0].gl_Position;
	vec4 v1 = gl_in[1].gl_Position;
	vec4 v2 = gl_in[2].gl_Position;

	float dx = abs(v0.x-v2.x)/sub_divisions;
	float dz = abs(v0.z-v1.z)/sub_divisions;
	float x=v0.x;
	float z=v0.z;

	for(int j=0;j<sub_divisions*sub_divisions;j++) 
	{
		gl_Position =  MVP * vec4(x,0,z,1);
		EmitVertex();
		gl_Position =  MVP * vec4(x,0,z+dz,1);
		EmitVertex();
		gl_Position =  MVP * vec4(x+dx,0,z,1);
		EmitVertex();
		gl_Position =  MVP * vec4(x+dx,0,z+dz,1);
		EmitVertex();
		EndPrimitive();
		x+=dx;
		if((j+1) %sub_divisions == 0) 
		{
		  x=v0.x;
		  z+=dz;
		}
	}

}