/**
 * @file  SynthetizeImage.cl
 * @brief Define the SynthetizeImage kernel.
 */

/**
 * @brief Synthetize the final image.
 * 
 * The image is synthetized by using the different materials 
 */
kernel void SynthetizeImage(__write_only image2d_t image, global SynthesisElement *synthesisBuffer, global Ray *rays, int screenWidth, int screenHeight /*, global Material *materials*/) {
	int x = get_global_id(0);
	int y = get_global_id(1);
	int i = x * screenHeight + y;
    
	Ray ray = rays[i];
	
	float distance = synthesisBuffer[i].distance;
	float3 normal = synthesisBuffer[i].normal;
	float3 point = synthesisBuffer[i].point;
	int	material = synthesisBuffer[i].material;
	
	if (distance > 0.00001f) {
		float4 white = {1.0f, 1.0f, 1.0f, 1.0f};
		float4 color = white/* * fabs(dot(ray.direction, normal))*/;
	
		write_imagef (image, (int2)(x, y), color);
	} else {
		write_imagef (image, (int2)(x, y), (float4)(0.0f, 0.0f, 0.0f, 1.0f));
	}
}
