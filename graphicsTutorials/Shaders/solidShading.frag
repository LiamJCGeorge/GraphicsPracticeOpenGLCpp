#version 130
#extension GL_ARB_gpu_shader5 : enable

out vec4 color;

uniform vec3 inColor;
uniform sampler2D box;

in VS_OUT
{
	vec4 color;
	vec2 uv;
} fs_in;

void main() {

	vec4 textureColor = texture(box, fs_in.uv);
	color =  fs_in.color * textureColor;

}