
#version 330

layout(location=0) in vec3 coord;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoord;

uniform mat4 WorldTransform;

out vec2 uv;

void main() {
	gl_Position = vec4(coord, 1.0f) * WorldTransform;
	uv = texCoord;
}
