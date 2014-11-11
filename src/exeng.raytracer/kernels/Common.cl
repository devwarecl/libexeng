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
