#version 130


in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 cam;

void main() {
	gl_Position.xy = (cam * vec4(vertexPosition, 0.0, 1.0)).xy;
	gl_Position.z = 0;
	gl_Position.w = 1;
	
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
	fragmentColor = vertexColor;
}

