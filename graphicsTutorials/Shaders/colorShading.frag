#version 130

in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D box;

void main() {

	vec4 textureColor = texture(box, fragmentUV);
	color = fragmentColor * textureColor;

}