/**
 * @brief Ray buffer generator kernel
 */

/** 
 * @brief Ray data structure.
 */
typedef struct {
	float3 point;		// Base point
	float3 direction;	// Normalized direction vector
} Ray;

typedef struct {
	float3 position;
	float3 lookAt;
	float3 up;
} Camera;

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
    float3 cam_right = cross(cam_up, cam_dir);
    
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
