#version 330 

in		vec2		uv;
out		vec4		outputColor;
uniform sampler2D	texSampler2D; 

void main() {
	outputColor = texture(texSampler2D, uv);
}
