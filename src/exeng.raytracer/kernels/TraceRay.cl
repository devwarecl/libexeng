
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
	
	if (distance > 0.0f) {
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

	if ((u > 0.0f && v > 0.0f && w > 0.0f) /* || (u < 0.0f && v < 0.0f && w < 0.0f)*/) {
		return true;
	} else {
		return false;
	}
}

constant vertex_t vertices[] =  {
	// Cara trasera
	{{-0.5f,   0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {0.0f, 1.0f}},  // Izquierda,  Arriba,  Atras
	{{ 0.5f,   0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {1.0f, 1.0f}},  // Derecha,    Arriba,  Atras
	{{-0.5f,  -0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {0.0f, 0.0f}},  // Izquierda,  Abajo,   Atras
	{{ 0.5f,  -0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {1.0f, 0.0f}},  // Derecha,    Abajo,   Atras

	// Cara derecha
	{{0.5f,   0.5f, -0.5f},   {1.0f, 0.0f, 0.0f},   {0.0f, 1.0f}}, // Derecha,     Arriba, Atras
	{{0.5f,   0.5f,  0.5f},   {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}}, // Derecha,     Arriba, Adelante
	{{0.5f,  -0.5f, -0.5f},   {1.0f, 0.0f, 0.0f},   {0.0f, 0.0f}}, // Derecha,     Abajo,  Atras
	{{0.5f,  -0.5f,  0.5f},   {1.0f, 0.0f, 0.0f},   {1.0f, 0.0f}}, // Derecha,     Abajo,  Adelante 

	// Cara delantera
	{{ 0.5f,   0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {1.0f, 1.0f}},  // Derecha,     Arriba, Adelante
	{{-0.5f,   0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {0.0f, 1.0f}},  // Izquierda,   Arriba, Adelante
	{{ 0.5f,  -0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {1.0f, 0.0f}},  // Derecha,     Abajo,  Adelante
	{{-0.5f,  -0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f}},  // Izquierda,   Abajo,  Adelante
	
	// Cara Izquierda
	{{-0.5f,   0.5f,  0.5f},  {-1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}}, // Izquierda,   Arriba, Adelante
	{{-0.5f,   0.5f, -0.5f},  {-1.0f, 0.0f, 0.0f},   {0.0f, 1.0f}}, // Izquierda,   Arriba, Atras
	{{-0.5f,  -0.5f,  0.5f},  {-1.0f, 0.0f, 0.0f},   {1.0f, 0.0f}}, // Izquierda,   Abajo,  Adelante 
	{{-0.5f,  -0.5f, -0.5f},  {-1.0f, 0.0f, 0.0f},   {0.0f, 0.0f}}, // Izquierda,   Abajo,  Atras
	
	// Cara de Arriba
	{{-0.5f,   0.5f,   0.5f},  {0.0f, 1.0f, 0.0f},   {0.0f, 1.0f}}, // Izquierda,   Arriba, Adelante
	{{ 0.5f,   0.5f,   0.5f},  {0.0f, 1.0f, 0.0f},   {1.0f, 1.0f}}, // Derecha,     Arriba, Adelante
	{{-0.5f,   0.5f,  -0.5f},  {0.0f, 1.0f, 0.0f},   {0.0f, 0.0f}}, // Izquierda,   Arriba, Atras
	{{ 0.5f,   0.5f,  -0.5f},  {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}},  // Derecha,     Arriba, Atras
	
	// Cara Inferior
	{{ 0.5f,  -0.5f,   0.5f},  {0.0f, -1.0f, 0.0f},   {1.0f, 1.0f}}, // Derecha,     Abajo, Adelante
	{{-0.5f,  -0.5f,   0.5f},  {0.0f, -1.0f, 0.0f},   {0.0f, 1.0f}}, // Izquierda,   Abajo, Adelante
	{{ 0.5f,  -0.5f,  -0.5f},  {0.0f, -1.0f, 0.0f},   {1.0f, 0.0f}}, // Derecha,     Abajo, Atras
	{{-0.5f,  -0.5f,  -0.5f},  {0.0f, -1.0f, 0.0f},   {0.0f, 0.0f}}  // Izquierda,   Abajo, Atras
};

constant int indices[] = {
	0 + 0,  0 + 1,  0 + 2,  0 + 1,  0 + 3,  0 + 2,
    4 + 0,  4 + 1,  4 + 2,  4 + 1,  4 + 3,  4 + 2, 
    8 + 0,  8 + 1,  8 + 2,  8 + 1,  8 + 3,  8 + 2, 
    12 + 0, 12 + 1, 12 + 2, 12 + 1, 12 + 3, 12 + 2, 
    16 + 0, 16 + 1, 16 + 2, 16 + 1, 16 + 3, 16 + 2, 
    20 + 0, 20 + 1, 20 + 2, 20 + 1, 20 + 3, 20 + 2
};

constant float3 screen_size = {640.0f, 480.0f, 0.0f};
constant float3 half_size = (float3)(639.0f * 0.5f, 479.0f * 0.5f, 0.0f);

/*
	ray_t cast_ray(int2 coords, float3 eye_coord) {
		float3 coordf = {(float)coords.x, (float)coords.y, 0.0f};

		ray_t ray = {
			eye_coord, 
			coordf - half_size + (float3)(0.5f, 0.5f, -150.0f)
		};

		return ray;
	}
*/

ray_t cast_ray(int2 coords, float3 eye_coord, float2 sample) {
	float3 coordf = {(float)coords.x, (float)coords.y, 0.0f};

	ray_t ray = {
		eye_coord, 
		normalize(coordf - half_size + (float3)(0.5f, 0.5f, 150.0f) + (float3)(sample.x, sample.y, 0.0f))
	};

	return ray;
}

/*
float _absf(float value) {
	if (value < 0.0f) {
		value = -value;
	}

	return value;
}
*/

float4 trace_ray(ray_t ray, float4 color, constant vertex_t *vertices, constant int *indices, int index_count) {
	intersect_info_t prev_info;
	intersect_info_t info;

	prev_info.distance = FLT_MAX;

	for (int i=0; i<index_count; i+=3) {
		float3 p1 = vertices[indices[i + 0]].coord;
		float3 p2 = vertices[indices[i + 1]].coord;
		float3 p3 = vertices[indices[i + 2]].coord;

		if (intersect_triangle(&info, ray, p1, p2, p3) && info.distance < prev_info.distance) {
			prev_info = info;
			
			// TODO: select the material of the mesh
			// 
			color = (float4)(1.0f, 1.0f, 1.0f, 1.0f) * fabs(dot(ray.direction, vertices[indices[i + 1]].normal));
		}
	}

	return color;
}

/**
 * @brief Main ray tracer kernel.
 */
__kernel void tracerKernel (
	__write_only image2d_t image, 
	global float2 *samples, 
	int sample_count, 
	float cam_x,
	float cam_y, 
	float cam_z) 
{
	// pixel coordinate.
	int2 coords = (int2)(get_global_id(0), get_global_id(1));

	// default background color
	float4 background_color = (float4)(0.0f, 0.0f, 1.0f, 1.0f);
	float4 color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	const int index_count = 36;

	// cast multisampled ray
	for (int i=0; i<sample_count; ++i) {
		ray_t ray = cast_ray(coords, (float3)(cam_x, cam_y, cam_z), samples[i]);
		// ray_t ray = cast_ray(coords, (float3)(cam_x, cam_y, cam_z), (float2)(0.0f, 0.0f));
		color += trace_ray(ray, background_color, vertices, indices, index_count);
	}

	color /= (float)sample_count;

	write_imagef (image, coords, color);
}
