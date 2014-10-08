/**
 * @file 	ComputeSynthesisData.cl
 * @brief 	This kernel compute the synthesis data (data needed for synthesize the final image) for the ray tracer for a 
 *		    single mesh subset data.
 */

/** 
 * @brief Ray data structure.
 */
typedef struct {
	float3 point;		// Base point
	float3 direction;	// Normalized direction vector
} Ray;

/** 
 * @brief Vertex data.
 */
typedef struct {
	float3 coord;		// Vertex position
	float3 normal;		// Vertex normalized normal vector
	float2 tex;			// Vertex texture coordinate
} Vertex;

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
 * @brief Plane
 */
typedef struct {
	float3 point;
	float3 normal;
} Plane;

/** 
 * @brief Camera definition
 */
typedef struct {
    float3 position;
    float3 look_at;
    float3 up;
} Camera;

/**
 * @brief Compute a synthesis element
 */
void computeElement(SynthesisElement *out, Ray ray, Plane plane) {
	float a = dot(plane.normal, plane.point - ray.point);
	float b = dot(plane.normal, ray.direction);
	float distance = a / b;
	
	out->distance = distance;
	out->normal = plane.normal;
	out->point = ray.point + ray.direction * distance;
}

/**
 * @brief Compute the triple dot product between three vectors.
 */
float triple(float3 a, float3 b, float3 c) {
	return dot(a, cross(b, c));
}

/**
 * @brief Compute a synthesis element for the specified triangle
 */
void computeElement(SynthesisElement *out, Ray ray, float3 p1, float3 p2, float3 p3, float3 normal) {	
	plane_t plane = {
		(p1 + p2 + p3) * (1.0f/3.0f), 
		normal
	};
	
	computeElement(out, ray, plane);
	
	float3 p = ray.point;
	float3 q = info->point;

	float3 pq = q - p;
	float3 pa = p1 - p;
	float3 pb = p2 - p;
	float3 pc = p3 - p;

	float u = triple(pq, pc, pb);
	float v = triple(pq, pa, pc);
	float w = triple(pq, pb, pa);

	return (u > 0.0f && v > 0.0f && w > 0.0f);
}

float4 traceRay(Ray ray, float4 color, global Vertex *vertices, global int *indices, int indexCount) {
	SynthesisElement prevElement;
	SynthesisElement element;
    
	prevElement.distance = FLT_MAX;
    
	for (int i=0; i<index_count; i+=3) {
		float3 p1 = vertices[indices[i + 0]].coord;
		float3 p2 = vertices[indices[i + 1]].coord;
		float3 p3 = vertices[indices[i + 2]].coord;
		
		float3 normal = vertices[indices[i + 0]].normal;
		
		computeElement(&element, ray, p1, p2, p3, normal);
		
		if (computeElement(&element, ray, p1, p2, p3) && element.distance < prevElement.distance) {
			prevElement = element;
			
			// TODO: select the material for the triangle
			// 
			// color = (float4)(1.0f, 1.0f, 1.0f, 1.0f) * fabs(dot(ray.direction, vertices[indices[i + 1]].normal));
            // color = (float4)(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
	
	return color;
}

/** 
 * @brief Populate the intersect info for the specified meshsubset
 */
kernel void intersectMeshSubset (
	global intersect_info_t *intersectInfo, int2 size, 
	global vertex_t *vertices, int vertexCount, 
	global int *indices, int indexCount,
	global float *materialData, 
	read_only image2d_t texImage) {

	int x = get_global_id(0);
	int y = get_global_id(1);

	int index = y * size.x + x;

	/* */
}

/**
 * @brief Main ray tracer kernel.
 */
__kernel void tracerKernel (
	__write_only image2d_t image, 
	global float2 *samples, 
	int sample_count, 
	float cx, float cy, float cz,
    float lx, float ly, float lz,
    float ux, float uy, float uz)
{
	// pixel coordinate.
	int2 coords = (int2)(get_global_id(0), get_global_id(1));
	
	// default background color
	float4 background_color = (float4)(0.0f, 0.0f, 1.0f, 1.0f);
	float4 color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	const int index_count = 36;
    
	// cast multisampled ray
	// for (int i=0; i<sample_count; ++i) {
	// 	ray_t ray = cast_ray(coords, camera[0], samples[i]);
	// 	color += trace_ray(ray, background_color, vertices, indices, index_count);
	// }
	// color /= (float)sample_count;
    
	// cast no multisampled ray
	ray_t ray = cast_ray(coords, (float3)(cx, cy, cz), (float3)(lx, ly, lz), (float2)(0.0f, 0.0f));
	color = trace_ray(ray, background_color, vertices, indices, index_count);
	
	write_imagef (image, coords, color);
}
