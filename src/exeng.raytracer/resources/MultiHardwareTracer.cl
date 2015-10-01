
/**
 * @file 	MultiHardwareTracer.cl
 * @brief 	Multi object, hardware-based, ray tracer source code.
 */

/** 
 * @brief Ray data structure.
 */
typedef struct {
	float4 point;		// Base point
	float4 direction;	// Normalized direction vector
} Ray;

/** 
 * @brief Vertex data.
 * This structure doesn't map portably to the Host.
 */
typedef struct {
	float4 coord;		// Vertex position
	float4 normal;		// Vertex normalized normal vector
	float4 tex;			// Vertex texture coordinate
} Vertex;

typedef struct {
	float4 p[3];
	float4 n;
} Triangle;

/**
 * @brief Synthesis Element.
 */
typedef struct {
	float4 	point;		// Point of intersection
	float4	normal;		// Normal vector of the surface that collided with the ray.
	float	distance;	// Distance from the origin of the ray.
	int		material;	// Material index/id (will be defined later).
} SynthesisElement;

/** 
 * @brief Plane
 */
typedef struct {
	float4 point;
	float4 normal;
} Plane;

/** 
 * @brief Camera definition
 */
typedef struct {
    float4 position;
    float4 lookAt;
    float4 up;
} Camera;

/**
 * @brief 4x4 Matrix structure
 */
typedef struct {
    float4 rows[4];
} Matrix;

float4 trans(Matrix matrix, float4 vector) 
{
    const float4 result = {
        dot(matrix.rows[0], vector),
        dot(matrix.rows[1], vector),
        dot(matrix.rows[2], vector),
        dot(matrix.rows[3], vector)
    };
    
    return result;
}

inline int coordToIndex(int x, int y, int width, int height) 
{
	return y*width + x;
}

/**
 * @brief Cast a perspective ray from the camera
 */
Ray cast(const Camera *camera, const float2 screenCoord, const float2 screenSize, const float2 sample)
{
    const float2 coordsf = screenCoord + sample;
	const float4 cam_pos = camera->position;
	
	const float4 cam_up = camera->up;	// assume a normalized vector
	const float4 cam_dir = normalize(camera->lookAt - cam_pos);
    // const float3 cam_right = normalize(cross(cam_up, cam_dir));
	const float4 cam_right = (float4)(normalize(cross(cam_dir.xyz, cam_up.xyz)), 0.0f);
    
    const float2 normalized_coords = (coordsf / (screenSize - (float2)(1.0f, 1.0f)) ) - (float2)(0.5f, 0.5f);
    const float4 image_point = normalized_coords.x * cam_right + normalized_coords.y * cam_up + cam_pos + cam_dir;
    
    const Ray ray = {
        cam_pos, 
        normalize(image_point - cam_pos) + (float4)(sample, 0.0f, 0.0f)
    };
    
    return ray;
}

__kernel void GenerateRays (
	global Ray *rays, 
	float camPosX, float camPosY, float camPosZ,
	float camLookAtX, float camLookAtY, float camLookAtZ, 
	float camUpX, float camUpY, float camUpZ,
	int screenWidth, int screenHeight) 
{
	const int x = get_global_id(0);
	const int y = get_global_id(1);
	const int i = coordToIndex(x, y, screenWidth, screenHeight);
	
	const float2 screenCoord = {(float)x, (float)y};
	const float2 screenSize = {(float)screenWidth, (float)screenHeight};

	const Camera camera = {
		{camPosX, camPosY, camPosZ, 1.0f},
		{camLookAtX, camLookAtY, camLookAtZ, 1.0f},
		{camUpX, camUpY, camUpZ, 0.0f},
	};
	
    *(rays + i) = cast(&camera, screenCoord, screenSize, (float2)(0.0f, 0.0f));
}

/**
 * @brief Compute a synthesis element
 */
void computeElementPlane(SynthesisElement *out, Ray ray, Plane plane) 
{
	const float a = dot(plane.normal, plane.point - ray.point);
	const float b = dot(plane.normal, ray.direction);

	const float distance = a / b;
	
	if (distance > 0.0f) {
		out->distance = distance;
		out->normal = plane.normal;
		out->point = ray.point + ray.direction * distance;
	}
}

/**
 * @brief Compute the triple dot product between three vectors.
 */
float triple(float3 a, float3 b, float3 c) 
{
	return dot(a, cross(b, c));
}

/**
 * @brief Compute a synthesis element for the specified triangle
 */
void computeElementTriangle(SynthesisElement *element, Ray ray, float4 p1, float4 p2, float4 p3, float4 normal) 
{
	const Plane plane = {
		(p1 + p2 + p3) * (1.0f/3.0f), 
		normal
	};
	
	SynthesisElement tempElement = {
		{0.0f, 0.0f, 0.0f, 0.0f}, 
		{0.0f, 0.0f, 0.0f, 0.0f}, 
		0.0f, 
		0
	};

	computeElementPlane(&tempElement, ray, plane);

    if (tempElement.distance <= 0.0f) {
        return;
    }

	const float3 p = ray.point.xyz;
	const float3 q = tempElement.point.xyz;

	const float3 pq = q - p;
	const float3 pa = p1.xyz - p;
	const float3 pb = p2.xyz - p;
	const float3 pc = p3.xyz - p;

	const float u = triple(pq, pc, pb);
	const float v = triple(pq, pa, pc);
	const float w = triple(pq, pb, pa);
	
	if (u > 0.0f && v > 0.0f && w > 0.0f) {
		*element = tempElement;
	}
}

/**
 * @brief Compute a synthesis element from a mesh subset
 */
void computeElementMeshSubset (
    global SynthesisElement *element, Ray ray, 
    global float *vertices, global int *indices, int indexCount, int materialIndex)
{
	// const int VertexSize = 32/4;	// = sizeof(exeng::Vertex)
	// const int CoordOffset = 0;
	// const int NormalOffset = 12/4;
	// const int TexCoordOffset = 24/4;
    global Vertex *vertexData = (global Vertex *)vertices;

	SynthesisElement bestElement = {{0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, 0.0f, 0};
	SynthesisElement currentElement = {{0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, 0.0f, 0};
	
	bestElement.distance = FLT_MAX;
	
	for (int i=0; i<indexCount; i+=3) {

		// render data from geometry mesh
        // global float* vertex1Ptr = vertexData + VertexSize*indices[i + 0];
        // global float* vertex2Ptr = vertexData + VertexSize*indices[i + 1];
        // global float* vertex3Ptr = vertexData + VertexSize*indices[i + 2];
        // global float* normalPtr = vertexData + VertexSize*indices[i + 0] + NormalOffset;
		// 
		// float4 coord1 = {vertex1Ptr[0], vertex1Ptr[1], vertex1Ptr[2], 0.0f};
		// float4 coord2 = {vertex2Ptr[0], vertex2Ptr[1], vertex2Ptr[2], 0.0f};
		// float4 coord3 = {vertex3Ptr[0], vertex3Ptr[1], vertex3Ptr[2], 0.0f};
		// float4 normal = {normalPtr[0], normalPtr[1], normalPtr[2], 1.0f};

		float4 coord1 = vertexData[indices[i + 0]].coord;
		float4 coord2 = vertexData[indices[i + 1]].coord;
		float4 coord3 = vertexData[indices[i + 2]].coord;
		float4 normal = vertexData[indices[i + 0]].normal;
		
		computeElementTriangle(&currentElement, ray, coord1, coord2, coord3, normal);
		
		if (currentElement.distance>0.0f && currentElement.distance<bestElement.distance) {
		 	bestElement = currentElement;
		}
	}
	
	if (bestElement.distance > 0.0f && bestElement.distance != FLT_MAX) {
		if (element->distance==0.0f || bestElement.distance<element->distance) {
			*element = bestElement;
			element->material = materialIndex;
		}
    }
}


/*
void computeElementMeshSubset (
    global SynthesisElement *element, Ray ray, 
    global float *vertices, global int *indices, int indexCount, int materialIndex)
{
	const int VertexSize = 32/4;	// = sizeof(exeng::Vertex)
	const int CoordOffset = 0;
	const int NormalOffset = 12/4;
	const int TexCoordOffset = 24/4;

    global float *vertexData = vertices;

	SynthesisElement bestElement = {{0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, 0.0f, 0};
	SynthesisElement currentElement = {{0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, 0.0f, 0};
	
	bestElement.distance = FLT_MAX;
	
	for (int i=0; i<indexCount; i+=3) {

		// render data from geometry mesh
        global float* vertex1Ptr = vertexData + VertexSize*indices[i + 0];
        global float* vertex2Ptr = vertexData + VertexSize*indices[i + 1];
        global float* vertex3Ptr = vertexData + VertexSize*indices[i + 2];
        global float* normalPtr = vertexData + VertexSize*indices[i + 0] + NormalOffset;
        
		float4 coord1 = {vertex1Ptr[0], vertex1Ptr[1], vertex1Ptr[2], 0.0f};
		float4 coord2 = {vertex2Ptr[0], vertex2Ptr[1], vertex2Ptr[2], 0.0f};
		float4 coord3 = {vertex3Ptr[0], vertex3Ptr[1], vertex3Ptr[2], 0.0f};
		float4 normal = {normalPtr[0], normalPtr[1], normalPtr[2], 1.0f};
		
		computeElementTriangle(&currentElement, ray, coord1, coord2, coord3, normal);
		
		if (currentElement.distance>0.0f && currentElement.distance<bestElement.distance) {
		 	bestElement = currentElement;
		}
	}
	
	if (bestElement.distance > 0.0f && bestElement.distance != FLT_MAX) {
		if (element->distance==0.0f || bestElement.distance<element->distance) {
			*element = bestElement;
			element->material = materialIndex;
		}
    }
}
*/

__kernel void ClearSynthesisData(global SynthesisElement *synthesisBuffer, int screenWidth, int screenHeight) 
{
    const int x = get_global_id(0);
    const int y = get_global_id(1);
    const int i = coordToIndex(x, y, screenWidth, screenHeight);
	const SynthesisElement element = {
		{0.0f, 0.0f, 0.0f, 0.0f},	// Point
		{0.0f, 0.0f, 0.0f, 0.0f},	// Normal
		0.0f,						// Distance
		0							// MaterialIndex
	};

	synthesisBuffer[i] = element;
}

/**
 * @brief Generate all the synthesis data to render a single object
 * This __kernel compute the data needed for synthesize the final image for the ray tracer of a 
 * single mesh subset data. It must be called multiple times, one for each meshSubset of each mesh, to render a complete scene.
 */
__kernel void ComputeSynthesisData (
	global SynthesisElement *synthesisBuffer, global Ray *rays, int screenWidth, int screenHeight,
	global float *vertices, global int *indices, int indexCount, int materialIndex, global float *localTransform)
{
	const int x = get_global_id(0);
	const int y = get_global_id(1);
	const int i = coordToIndex(x, y, screenWidth, screenHeight);
    
	global Matrix *transforms = (global Matrix*)localTransform;

	Ray ray = rays[i];
	ray.point		= trans(transforms[1], ray.point);
	ray.direction	= trans(transforms[1], ray.direction);

	computeElementMeshSubset(&synthesisBuffer[i], ray, vertices, indices, indexCount, materialIndex);
}

/**
 * @brief Synthetize the final image.
 * 
 * The image is synthetized by using the different materials 
 */
__kernel void SynthetizeImage (
    write_only image2d_t image, 
    global SynthesisElement *synthesisBuffer, 
	global Ray *rays, int screenWidth, int screenHeight, 
    int materialSize, global float *materialData)
{
	const int x = get_global_id(0);
	const int y = get_global_id(1);
	const int i = coordToIndex(x, y, screenWidth, screenHeight);
    
	const Ray ray = rays[i];
	const SynthesisElement synthElement = synthesisBuffer[i];
    
	const float4 color = *((global float4 *)(materialData + synthElement.material*materialSize));
	const float4 finalColor = color * fabs(dot(ray.direction, synthElement.normal));

	write_imagef (image, (int2)(x, y), finalColor);
}

__kernel void GetStructuresSize(global int* out) 
{
	out[0] = sizeof(Ray);
	out[1] = sizeof(SynthesisElement);
	out[2] = sizeof(Vertex);
}
