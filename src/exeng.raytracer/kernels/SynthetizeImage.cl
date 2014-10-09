/**
 * @file  SynthetizeImage.cl
 * @brief Define the SynthetizeImage kernel.
 */

/**
 * @brief Synthesis Element.
 */
typedef struct {
	float	distance;	// Distance from the origin of the ray.
	float3	normal;		// Normal vector of the surface that collided with the ray.
	float3 	point;		// Point of intersection
	int		material;	// Material index/id (will be defined later).
} SynthesisElement;

/**
 * @brief Synthetize the final image.
 * 
 * The image is synthetized by using the different materials 
 */
kernel void SynthetizeImages(__write_only image2d_t image, global SynthesisElement *synthesisBuffer, global Ray *rays, int screenWidth, int screenHeight, global Material *materials) {
	int x = get_global_id(0);
	int y = get_global_id(1);
	int i = x * screenHeight + y;
	
	Ray ray = rays[i];
	
	float distance = synthesisBuffer[i].distance;
	float3 normal = synthesisBuffer[i].normal;
	float3 point = synthesisBuffer[i].point;
	int	material = synthesisBuffer[i].material;
	
	float4 white = {1.0f, 1.0f, 1.0f, 1.0f};
	
	float4 color = white * fabs(dot(ray.direction, normal));
	
	write_imagef (image, coords, color);
}
