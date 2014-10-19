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

