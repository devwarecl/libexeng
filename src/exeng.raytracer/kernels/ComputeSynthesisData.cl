/**
 * @file 	ComputeSynthesisData.cl
 * @brief 	This kernel compute the synthesis data (data needed for synthesize the final image) for the ray tracer for a 
 *		    single mesh subset data. It must be called multiple times, one for meshSubset, to render a complete scene.
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
void computeElementPlane(SynthesisElement *out, Ray ray, Plane plane) {
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
void computeElementTriangle(SynthesisElement *element, Ray ray, float3 p1, float3 p2, float3 p3, float3 normal) {	
	plane_t plane = {
		(p1 + p2 + p3) * (1.0f/3.0f), 
		normal
	};
	
	computeElementPlane(element, ray, plane);
	
	float3 p = ray.point;
	float3 q = info->point;

	float3 pq = q - p;
	float3 pa = p1 - p;
	float3 pb = p2 - p;
	float3 pc = p3 - p;

	float u = triple(pq, pc, pb);
	float v = triple(pq, pa, pc);
	float w = triple(pq, pb, pa);
	
	float result = (float)(u > 0.0f && v > 0.0f && w > 0.0f);
	
	element->point *= result;
	element->distance *= result;
	element->normal *= result;
}

/**
 * @brief Compute a synthesis element from a mesh subset
 */
void computeElementMeshSubset(global SynthesisElement *element, Ray ray, global Vertex *vertices, global int *indices, int indexCount) {
	SynthesisElement bestElement;
	SynthesisElement currentElement;
	
	bestElement.distance = FLT_MAX;
	
	float factor;
	
	for (int i=0; i<index_count; i+=3) {
		float3 normal = vertices[indices[i + 0]].normal;
		float3 p1 = vertices[indices[i + 0]].coord;
		float3 p2 = vertices[indices[i + 1]].coord;
		float3 p3 = vertices[indices[i + 2]].coord;
		
		computeElementTriangle(&currentElement, ray, p1, p2, p3, normal);
		
		bestElement.distance = (bestElement.distance<currentElement.distance) ? bestElement.distance : currentElement.distance;
		
		// if (computeElement(&element, ray, p1, p2, p3) && element.distance < prevElement.distance) {
		// 	prevElement = element;
		// }
	}
	
	*element = bestElement;
}

/**
 * @brief Generate all the synthesis data to render a single object
 */
__kernel void ComputeSynthesisData (
	global SynthesisData *synthesisBuffer, global Ray *rays, int2 screenSize,
	global Vertex *vertices, global int *indices, int indexCount, int materialIndex) {
	
	int x = get_global_id(0);
	int y = get_global_id(1);
	int i = x * screenSize.y + y;
	
	Ray ray = rays[i];
	
	computeElementMeshSubset(synthesisBuffer + i, ray, vertices, indices, indexCount);
}
