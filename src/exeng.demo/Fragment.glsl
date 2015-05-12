#version 330

in		vec2		uv;
out		vec4		fragmentColor;
uniform	sampler2D	textureSampler;

void main() 
{
	// fragmentColor = texture(textureSampler, uv);
	fragmentColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
