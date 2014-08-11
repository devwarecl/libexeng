
typedef struct {
	float3 point;		// Base point
	float3 direction;	// Normalized direction vector
} ray_t ;

typedef struct {
	float3 coord;		// Vertex position
	float3 normal;		// Vertex normalized normal vector
	float2 tex;			// Vertex texture coordinate
} vertex_t;

typedef struct {
	float	distance;
	float3	normal;
} intersect_info_t;

typedef struct {
	float3 point;
	float3 normal;
} plane_t;

bool intersect_plane(intersect_info_t *info, ray_t ray, plane_t plane) {
	float distance = dot(plane.normal, plane.point - ray.point) / dot(plane.normal, ray.direction);
	
	if (distance > 0.0) {
		info->distance = distance;
		info->normal = plane.normal;

		return true;
	} else {
		return false;
	}
}

float triple(float3 a, float3 b, float3 c) {
	return dot(a, cross(b, c));
}

bool intersect_triangle(intersect_info_t *info, ray_t ray, float3 p1, float3 p2, float3 p3) {	
	plane_t plane = {
		(p1 + p2 + p3) / 3.0f, 
		normalize(cross(p2 - p1, p3 - p1))
	};

	if (!intersect_plane(info, ray, plane)) {
		return false;
	}

	float3 p = ray.point;
	float3 q = ray.point + ray.direction * info->distance;

	float3 pq = q - p;
	float3 pa = p1 - p;
	float3 pb = p2 - p;
	float3 pc = p3 - p;

	float u = triple(pq, pc, pb);
	float v = triple(pq, pa, pc);
	float w = triple(pq, pb, pa);

	if (u > 0.0 && v > 0.0 && w > 0.0) {
		return true;
	} else {
		return false;
	}
}

__constant vertex_t vertices[3] =  {
	{{10.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
	{{10.0f, 30.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
	{{40.0f, 10.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}
};

__constant int indices[] = {
	0, 1, 2
};

/**
 * @brief Main ray tracer kernel.
 */
__kernel void tracerKernel(__write_only image2d_t image) {
	// Pixel coordinate.
	int2 coords = (int2)(get_global_id(0), get_global_id(1));

	// Default background color
	float4 color = (float4)(0.0f, 0.0f, 1.0f, 1.0f);	

	// cast a ray
	ray_t ray = {
		{(float)coords.x, (float)coords.y, -10.0}, 
		{0.0, 0.0, 1.0}
	};

	const int triangle_count = 1;

	intersect_info_t info;

	// draw indexed mesh
	for (int i=0; i<triangle_count*3; i+=3) {
		float3 p1 = vertices[indices[i + 0]].coord;
		float3 p2 = vertices[indices[i + 1]].coord;
		float3 p3 = vertices[indices[i + 2]].coord;

		if (intersect_triangle(&info, ray, p1, p2, p3)) {
			color = (float4)(1.0, 1.0, 1.0, 1.0);
		}
	}

	write_imagef (image, coords, color);
}
