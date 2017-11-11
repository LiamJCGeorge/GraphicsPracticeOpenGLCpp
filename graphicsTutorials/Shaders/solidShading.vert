#version 130
#extension GL_ARB_gpu_shader5 : enable


in vec3 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out VS_OUT
{
	vec4 color;
	vec2 uv;
} vs_out;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;



void main() {
	
	vec4 p = vec4(vertexPosition,1);
    gl_Position = proj * view * model * p;
	
	if (vertexColor.rgb == vec3(0,0,0))
		vs_out.color = p * 2.0 + vec4(0.5,0.5,0.5,1);
	else
		vs_out.color = vertexColor;
		
	vs_out.uv = vertexUV;
}