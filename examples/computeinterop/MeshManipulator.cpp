
#include "MeshManipulator.hpp"

#include <cassert>
#include <xe/gfx/Mesh.hpp>
#include <xe/gfx/MeshSubset.hpp>

std::string kernel_src = R"(
    typedef struct {
        float3 position;
        float3 normal;
        float2 texcoord;
    } 
    vertex_t;
    
    // Just scales the mesh position by a small margin
    __kernel void manipulateMesh(__global __read_write vertex_t* vertices) {
        const int i = get_global_id(0);
        
        vertices[i].position *= 1.00001f;
    }
)";

MeshManipulator::MeshManipulator(xe::cm::ComputeModulePtr computeModule_, xe::gfx::GraphicsDriver *graphicsDriver) {
	assert(graphicsDriver);

	computeModule = std::move(computeModule_);
	
	xe::cm::Device* device = this->findDevice();
	assert(device);

    context = device->createContext(graphicsDriver);
    queue = context->createQueue();
    program = context->createProgram(kernel_src);
    manipulateMeshKernel = context->createKernel(program.get(), "manipulateMesh");
}

MeshManipulator::~MeshManipulator() {}

void MeshManipulator::manipulate(xe::gfx::Mesh *mesh) {
	assert(mesh);
    	
	for (int i=0; i<mesh->getSubsetCount(); i++) {
        xe::gfx::MeshSubset *subset = mesh->getSubset(i);
        xe::Buffer *buffer = subset->getBuffer(0);
        
        // prepare kernel for execution
        manipulateMeshKernel->setArg(0, buffer);
        
        // execute the kernel
        queue->enqueueKernel(manipulateMeshKernel.get(), subset->getVertexCount());
	}
}

xe::cm::Device* MeshManipulator::findDevice() const {
    xe::cm::Device *device = nullptr;
    
    // find device
    auto platforms = computeModule->enumeratePlatforms();

    std::cout << "Found " << platforms.size() << " platform(s)." << std::endl;
        
    for (xe::cm::Platform *platform : platforms) {
        auto devices = platform->enumerateDevices();
            
        std::cout << "Found " << devices.size() << " device(s)." << std::endl;
            
        for (xe::cm::Device *device_ : devices) {
            auto info = device_->getInfo();
            
			if (info.getType() == xe::cm::DeviceType::GPU) {
				std::cout << "Using " << info.getName() << ", " << info.getVendor() << std::endl;
				device = device_;
				break;
			}
        }
    }
    
	if (!device) {
		std::cout << "No GPU device found!" << std::endl;
	}

    return device;
}
