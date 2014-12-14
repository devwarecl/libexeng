/**
 * @file 	Commmon.cl
 * @brief 	Common structures and definitions.
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
    float3 lookAt;
    float3 up;
} Camera;

typedef struct {
    float foo;
} Material;


/*sample cube data*/
/*
constant Vertex vertices_[] =  {
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

constant int indices_[] = {
    0 + 0,  0 + 1,  0 + 2,  0 + 1,  0 + 3,  0 + 2,
    4 + 0,  4 + 1,  4 + 2,  4 + 1,  4 + 3,  4 + 2, 
    8 + 0,  8 + 1,  8 + 2,  8 + 1,  8 + 3,  8 + 2, 
    12 + 0, 12 + 1, 12 + 2, 12 + 1, 12 + 3, 12 + 2, 
    16 + 0, 16 + 1, 16 + 2, 16 + 1, 16 + 3, 16 + 2, 
    20 + 0, 20 + 1, 20 + 2, 20 + 1, 20 + 3, 20 + 2
};
*/

constant Vertex vertices_[] =  {
    // Cara trasera
    {{-0.5f,   0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {0.0f, 1.0f}},  // Izquierda,  Arriba,  Atras
    {{ 0.5f,   0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {1.0f, 1.0f}},  // Derecha,    Arriba,  Atras
    {{-0.5f,  -0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {0.0f, 0.0f}},  // Izquierda,  Abajo,   Atras
    {{ 0.5f,  -0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {1.0f, 0.0f}},  // Derecha,    Abajo,   Atras
};

constant int indices_[] = {
    0 + 0,  0 + 1,  0 + 2,  0 + 1,  0 + 3,  0 + 2
};


/**
 * @brief Ray buffer generator kernel
 */

// constant float3 screen_size = {640.0f, 480.0f, 0.0f};
// constant float3 half_size = (float3)(639.0f * 0.5f, 479.0f * 0.5f, 0.0f);

/**
 * @brief Cast a perspective ray from the camera
 */
void castRay(global Ray *rayOut, Camera *camera, float2 screenCoord, float2 screenSize, float2 sample) {
    // float3 coordsf = (float3)(screenCoord, 0.0f) + (float3)(sample, 0.0f);
    float2 coordsf = screenCoord + sample;

	float3 cam_pos = camera->position;
	float3 cam_up = camera->up;	// assume a normalized vector
	float3 cam_dir = normalize(camera->lookAt - cam_pos);
    float3 cam_right = normalize(cross(cam_up, cam_dir));
    
    float2 normalized_coords = (coordsf / screenSize) - (float2)(0.5f, 0.5f);
    float3 image_point = normalized_coords.x * cam_right + normalized_coords.y * cam_up + cam_pos + cam_dir;
    
    Ray ray = {
        cam_pos, 
        normalize(image_point - cam_pos) + (float3)(sample, 0.0f)
    };
    
    *rayOut = ray;
}

kernel void GenerateRays (
	global Ray *rays, 
	float camPosX, float camPosY, float camPosZ,
	float camLookAtX, float camLookAtY, float camLookAtZ, 
	float camUpX, float camUpY, float camUpZ,
	int screenWidth, int screenHeight) {

	int x = get_global_id(0);
	int y = get_global_id(1);
	
	int i = x*screenHeight + y;
	
	float2 screenCoord = {(float) x, (float)y};
	float2 screenSize = {(float)screenWidth, (float)screenHeight};

	Camera camera = {
		{camPosX, camPosY, camPosZ},
		{camLookAtX, camLookAtY, camLookAtZ},
		{camUpX, camUpY, camUpZ},
	};
	
	castRay(rays+i, &camera, screenCoord, screenSize, (float2)(0.0f, 0.0f));
}


/**
 * @file  ComputeSynthesisData.cl
 * @brief This kernel compute the synthesis data (data needed for synthesize the final image) for the ray tracer for a 
 *		  single mesh subset data. It must be called multiple times, one for meshSubset, to render a complete scene.
 */

/**
 * @brief Compute a synthesis element
 */
void computeElementPlane(SynthesisElement *out, Ray ray, Plane plane) {
	float a = dot(plane.normal, plane.point - ray.point);
	float b = dot(plane.normal, ray.direction);
	float distance = a / b;
	
	if (distance > 0.0f) {
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
	
	SynthesisElement tempElement;

	computeElementPlane(&tempElement, ray, plane);
    if (tempElement.distance <= 0.0f) {
        return;
    }

	float3 p = ray.point;
	float3 q = tempElement.point;

	float3 pq = q - p;
	float3 pa = p1 - p;
	float3 pb = p2 - p;
	float3 pc = p3 - p;

	float u = triple(pq, pc, pb);
	float v = triple(pq, pa, pc);
	float w = triple(pq, pb, pa);
	
	if (u > 0.0f && v > 0.0f && w > 0.0f) {
		*element = tempElement;
	}
}

/**
 * @brief Compute a synthesis element from a mesh subset
 */
void computeElementMeshSubset(global SynthesisElement *element, Ray ray, constant Vertex *vertices, constant int *indices, int indexCount) {
	SynthesisElement bestElement = {0.0f};
	SynthesisElement currentElement = {0.0f};
	
	bestElement.distance = FLT_MAX;
	
	float factor;
	
	for (int i=0; i<indexCount; i+=3) {
		float3 normal = vertices[indices[i + 0]].normal;
		float3 p1 = vertices[indices[i + 0]].coord;
		float3 p2 = vertices[indices[i + 1]].coord;
		float3 p3 = vertices[indices[i + 2]].coord;
		
		computeElementTriangle(&currentElement, ray, p1, p2, p3, normal);
		
		if (currentElement.distance>0.0f && currentElement.distance<bestElement.distance) {
		 	bestElement = currentElement;
		}
	}
	
	if (bestElement.distance > 0.0f && bestElement.distance != FLT_MAX) {
        *element = bestElement;
    }
}

__kernel void ClearSynthesisData(global SynthesisElement *synthesisBuffer, int screenWidth, int screenHeight) {
    int x = get_global_id(0);
    int y = get_global_id(1);
    int i = x * screenHeight + y;
    
    synthesisBuffer[i].distance = 0.0f;
    synthesisBuffer[i].normal = (float3)(0.0f, 0.0f, 0.0f);
    synthesisBuffer[i].point = (float3)(0.0f, 0.0f, 0.0f);
    synthesisBuffer[i].material = 0;
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
	
	computeElementMeshSubset(synthesisBuffer + i, ray, vertices_, indices_, sizeof(indices_)/sizeof(indices_[0]));
}

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
