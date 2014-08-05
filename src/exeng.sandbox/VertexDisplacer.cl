
__kernel void VertexDisplacer(__write_only image2d_t img, float displace) {

	const sampler_t sampler =	CLK_NORMALIZED_COORDS_FALSE	|
								CLK_ADDRESS_CLAMP_TO_EDGE	|
								CLK_FILTER_LINEAR;
	
	int2 coord = (int2)(get_global_id(0), get_global_id(1));

	uint4 color;
	color.x = color.y = color.z = 125;
	color.w = 255;

	write_imageui(img, coord, color);
}
