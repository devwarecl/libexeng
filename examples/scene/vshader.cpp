
#include "vshader.hpp"

std::string vshader_src = R"(#version 330
layout(location=0) in vec3 coord;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 tex_coord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
// uniform mat4 mvp;

out vec3 n;
out vec2 uv;

void main() {
	mat4 mvp = model * view * proj;

	gl_Position = vec4(coord, 1.0f) * mvp;
	n = vec3(vec4(normal, 1.0f) * mvp);
	uv = tex_coord;
})";
