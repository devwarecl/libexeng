/**
 * @file RayTracer.hpp
 * @brief Interfaz del objeto trazador de rayos
 */


#include "RayTracer.hpp"
#include <CL/cl.h>

using namespace exeng;
using namespace exeng::graphics;
using namespace exeng::scenegraph;

namespace raytracer {

struct RayTracer::Private {
    Texture *renderTarget;
    const Scene *scene;
    cl_platform_id platformId;    
    cl_device_id deviceId;
    cl_context context;
    cl_command_queue queue;
    
    Private() {
        this->renderTarget = nullptr;
        this->scene = nullptr;
        this->platformId = 0;
        this->deviceId = 0;
        this->context = nullptr;
        this->queue = nullptr;
    }
    
    ~Private() {
        this->renderTarget = nullptr;
        this->scene = nullptr;
        
        
        if (this->queue != nullptr) {
            ::clReleaseCommandQueue(this->queue);
        }
        
        if (this->context != nullptr) {
            ::clReleaseContext(this->context);
        }
    }
};


RayTracer::RayTracer( Texture &renderTarget, const Scene &scene ) : impl(new RayTracer::Private()) {
    cl_platform_id platformId = 0;
    cl_uint platformIdCount = 1;
    cl_int errorCode = 0;
    
    // Obtener la primera plataforma
    errorCode = ::clGetPlatformIDs(1, &platformId, &platformIdCount);
    
    if (errorCode != CL_SUCCESS) {
        throw std::runtime_error("RayTracer::RayTracer: Error al obtener las plataformas disponibles.");
    }
    
    // Obtener el primer device
    cl_device_id deviceId = 0;
    errorCode = ::clGetDeviceIDs(platformId, CL_DEVICE_TYPE_GPU, 1, &deviceId, nullptr);
    
    if (errorCode != CL_SUCCESS) {
        throw std::runtime_error("RayTracer::RayTracer: Error al obtener un dispositivo.");
    }
    
    // Crear un contexto
    cl_context context = nullptr;
    context = ::clCreateContext(nullptr, 1, &deviceId, nullptr, nullptr, &errorCode);
    
    if (errorCode != CL_SUCCESS) {
        throw std::runtime_error("RayTracer::RayTracer: Error al crear un contexto");
    }
    
    // Crear una cola de comandos
    cl_command_queue queue = nullptr;
    queue = ::clCreateCommandQueue(context, deviceId, 0, nullptr);
    
    this->impl->renderTarget = &renderTarget;
    this->impl->scene = &scene;
    this->impl->platformId = platformId;
    this->impl->deviceId = deviceId;
    this->impl->context = context;
    this->impl->queue = queue;
}


void RayTracer::render() {
    const Scene *scene = this->impl->scene;
    Texture *renderTarget = this->impl->renderTarget;
}


RayTracer::~RayTracer() {
    
}

}
