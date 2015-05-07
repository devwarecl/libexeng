#version 330

uniform mat4 WorldTransform;

in vec4 coord;
in vec3 normal;
in vec2 texCoord;

out vec2 uv;

void main() 
{
	gl_Position = coord * WorldTransform;
	uv = texCoord;
}
