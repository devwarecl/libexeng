/**
 * @file 	ComputeSynthesisData.cl
 * @brief 	This kernel compute the synthesis data (data needed for synthesize the final image) for the ray tracer for a 
 *		    single mesh subset data. It must be called multiple times, one for meshSubset, to render a complete scene.
 */

/**
 * @brief Compute a synthesis element
 */
void computeElementPlane(SynthesisElement *out, Ray ray, Plane plane) {
	float a = dot(plane.normal, plane.point - ray.point);
	float b = dot(plane.normal, ray.direction);

	float distance = a / b;
	
    if (distance <= 0.0f) {
        out->distance = 0.0f;
	    out->normal = (float3)(0.0f, 0.0f, 0.0f);
	    out->point = (float3)(0.0f, 0.0f, 0.0f);
    } else {
        out->distance = distance;
	    out->normal = plane.normal;
	    out->point = ray.point + ray.direction * distance;
    }
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
	Plane plane = {
		(p1 + p2 + p3) * (1.0f/3.0f), 
		normal
	};
	
	computeElementPlane(element, ray, plane);
    // if (element->distance == 0.0f) {
    //     return;
    // }

	float3 p = ray.point;
	float3 q = element->point;

	float3 pq = q - p;
	float3 pa = p1 - p;
	float3 pb = p2 - p;
	float3 pc = p3 - p;

	float u = triple(pq, pc, pb);
	float v = triple(pq, pa, pc);
	float w = triple(pq, pb, pa);
	
    // this gives 1 or 0
	float result = (float)(u > 0.0f && v > 0.0f && w > 0.0f);   

	element->point *= result;
	element->distance *= result;
	element->normal *= result;
}

/**
 * @brief Compute a synthesis element from a mesh subset
 */
void computeElementMeshSubset(global SynthesisElement *finalElement, Ray ray, global Vertex *vertices, global int *indices, int indexCount) {
	SynthesisElement prev;
	SynthesisElement element;
	
	prev.distance = FLT_MAX;
	
	float factor;
	
	for (int i=0; i<indexCount; i+=3) {
		float3 normal = vertices[indices[i + 0]].normal;
		float3 p1 = vertices[indices[i + 0]].coord;
		float3 p2 = vertices[indices[i + 1]].coord;
		float3 p3 = vertices[indices[i + 2]].coord;
		
		computeElementTriangle(&element, ray, p1, p2, p3, normal);
		
		if (element.distance < prev.distance) {
		    prev = element;
		}
	}
	
    if (element.distance > 0.0f) {
        *finalElement = element;
    }
}

/**
 * @brief Generate all the synthesis data to render a single object
 */
__kernel void ComputeSynthesisData (
	global SynthesisElement *synthesisBuffer, global Ray *rays, int screenWidth, int screenHeight,
	global Vertex *vertices, global int *indices, int indexCount, int materialIndex) {
	
	int x = get_global_id(0);
	int y = get_global_id(1);
	int i = x * screenHeight + y;
	
	Ray ray = rays[i];
	
	computeElementMeshSubset(synthesisBuffer + i, ray, vertices, indices, indexCount);
}
