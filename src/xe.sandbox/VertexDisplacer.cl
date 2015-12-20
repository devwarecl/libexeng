
float lerp(float a, float b, float t) {
	return a*(1.0 - t) + b*t;
}

float clerp(float a, float b, float t) {
	t = t * 3.1415926535;
	t = (1.0 - cos(t)) * 0.5;

	return lerp(a, b, t);
}

float slerp(float a, float b, float c, float d, float t) {
	float p = (d - c) - (b - a);
	float q = (b - a) - p;
	float r = c - a;
	float s = b;
	float t_2 = t*t;
	float t_3 = t_2*t;

	return p*t_3 + q*t_2 + r*t + s;
}

float noise2d (int x, int y) {
	int n  = x *+ y * 57;
	n = (n << 13) ^ n;

	return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);    
}

float snoise2d(int x, int y) {
	float corners = (noise2d(x - 1, y - 1)	+ noise2d(x + 1, y - 1) + noise2d(x - 1, y + 1) + noise2d(x + 1, y + 1)) / 16.0;
	float sides	=	(noise2d(x - 1, y	 )	+ noise2d(x + 1, y	  ) + noise2d(x	   , y - 1) + noise2d(x    , y + 1)) / 8.0;
	float center =	noise2d(x, y) / 4.0;

	return corners + sides + center;
}

float lerp_noise2d(float x, float y) {
	int intX = (int)x;
	int intY = (int)y;

	float tX = x - intX;
	float tY = y - intY;

	float v1 = snoise2d(intX + 0, intY + 0);
	float v2 = snoise2d(intX + 1, intY + 0);
	float v3 = snoise2d(intX + 0, intY + 1);
	float v4 = snoise2d(intX + 1, intY + 1);

	float a = clerp(v1, v2, tX);
	float b = clerp(v3, v4, tX);

	return clerp(a, b, tY);
}

float perlin_noise2d(float x, float y) {
	float total = 0.0;

	int n = 4; /*octaves*/
	float p = 0.25; /*persistence*/

	int freq = 0;
	int amp = 0;

	for (int i=0; i<n; ++i) {
		freq = pown(2.0, i);
		amp = pow(p, i);

		total += lerp_noise2d(x * freq, y * freq) * amp;
	}

	return total;
}

__kernel void VertexDisplacer(__write_only image2d_t img, float displace) {
	int2 coord = (int2)(get_global_id(0), get_global_id(1));

	float x = (float) coord.x;
	float y = (float) coord.y;
	float c = perlin_noise2d(x, y);

	/*
	if (x < y) {
		c = x / y;
	} else {
		c = y / x;
	}
	*/

	float4 color = (float4)(0.4, c, c, 1.0);
	write_imagef(img, coord, color);
}
