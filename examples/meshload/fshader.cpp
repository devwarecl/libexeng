
#include "fshader.hpp"

std::string fshader_src = 
R"(
#version 330

in vec3 n;
in vec2 uv;

out vec4 color;

uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform vec4 emissive;
uniform float shininess;

uniform sampler2D tex_sampler;

void main() {
	vec4 light_direction = normalize(vec4(0.0f, -1.0f, 0.25f, 0.0f));
	float factor = dot(light_direction, vec4(n, 1.0f));	

	// color = /*texture(tex_sampler, uv) * */ambient * factor;
	color = diffuse * factor;
	// color = ambient;	
}

)";
