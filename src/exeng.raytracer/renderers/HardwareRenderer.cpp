
#include "HardwareRenderer.hpp"
#include "HardwareRendererPrivate.hpp"

#include <ostream>
#include <fstream>
#include <iomanip>
#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>

namespace exeng { namespace raytracer { namespace renderers {
    
    using namespace exeng::graphics;
    using namespace exeng::scenegraph;

    HardwareRenderer::HardwareRenderer(Texture *renderTarget, const AssetLibrary *assets, const MaterialLibrary *materialLibrary) {
        this->impl = std::make_unique<HardwareRendererPrivate>();

        BOOST_LOG_TRIVIAL(trace) << "Initializing Multi-Object ray tracer ...";
		
        cl::Platform platform;  // selected platform
        cl::Device device;      // selected device
        bool deviceFound = false;
        
		std::vector<cl::Platform> platforms;
		cl::Platform::get(&platforms);
        
        BOOST_LOG_TRIVIAL(trace) << "Found " << platforms.size() << " platform(s).";
        
        if (platforms.size() == 0) {
            throw std::runtime_error("HardwareTracer::HardwareTracer: No OpenCL platforms available");
        }
        
        for (cl::Platform &platform_ : platforms) {
            std::vector<cl::Device> devices;
            platform_.getDevices(CL_DEVICE_TYPE_GPU, &devices);

            // Select the first platform
            BOOST_LOG_TRIVIAL(trace) 
                << "Found " << devices.size() << " device(s) for platform "
                << "with platform: " << platform.getInfo<CL_PLATFORM_NAME>(nullptr);
            
            if (devices.size() > 0) {
                platform = platform_;
                device = devices[0];
                deviceFound = true;
                
                BOOST_LOG_TRIVIAL(trace) << "Using OpenCL device: " << device.getInfo<CL_DEVICE_NAME>(nullptr);
                
                break;
            }
        }
        
        if (!deviceFound) {
            throw std::runtime_error("HardwareTracer::HardwareTracer: No OpenCL GPU devices available");
        }
        
		BOOST_LOG_TRIVIAL(trace) << "Creating OpenCL context with GL/CL interop support....";
        
		// Set context properties for GL/CL interop.
		cl_context_properties properties[] = {
			// We need to add information about the OpenGL context with
			// which we want to exchange information with the OpenCL context.
#if defined (WIN32)
			// We should first check for cl_khr_gl_sharing extension.
			CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(),
			CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(),
#elif defined (__linux__)
			// We should first check for cl_khr_gl_sharing extension.
			CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(),
			CL_GLX_DISPLAY_KHR, (cl_context_properties)glXGetCurrentDisplay(),
#elif defined (__APPLE__)
			CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE, (cl_context_properties)CGLGetShareGroup(CGLGetCurrentContext()),
#endif
			CL_CONTEXT_PLATFORM, (cl_context_properties)platform(),
			0, 0,
		};
        
		// initialize the OpenCL context
		cl::Context context = cl::Context(device, properties);
        
		// pass the samples to OpenCL
		cl::Buffer samplesBuffer;

		//if (sampler) {
		//	BOOST_LOG_TRIVIAL(trace) << "Creating sampling buffer from " << sampler->getSampleCount() << " sample(s)...";
		//	size_t bufferSize = sizeof(Vector2f) * sampler->getSampleCount();
		//	cl_mem_flags bufferFlags = CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR;
		//	void* bufferData = (void*)(sampler->getSampleData());

		//	samplesBuffer = cl::Buffer(context, bufferFlags, bufferSize, bufferData);
		//}

		// Create a Program object from all the kernels
        const Buffer *hardwareTracerBuffer  = assets->getAsset("MultiHardwareTracer.cl");
        cl::Program::Sources programSources = { {(const char*)hardwareTracerBuffer->getPointer(), hardwareTracerBuffer->getSize()} };

		// Compile the OpenCL programs
		std::string programOptions = "-Werror";
		// programOptions += "-Werror";
		// programOptions += "\"" + getRootPath() + "kernels/MultiHardwareTracer.cl\"";
		
		cl::Program program = cl::Program(context, programSources);
		if (program.build({device}, programOptions.c_str()) != CL_SUCCESS) {
			std::string msg;
			msg += "OpenCL program compile error: ";
			msg += program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);
			msg += "\n";

			throw std::runtime_error(msg);
		}

		BOOST_LOG_TRIVIAL(trace) << "Completing Multi-Object ray tracer initialization ...";

		cl::Kernel clearSynthBufferKernel       = cl::Kernel(program, "ClearSynthesisData");
		cl::Kernel rayGeneratorKernel			= cl::Kernel(program, "GenerateRays");
		cl::Kernel rayGeneratorFromMatrixKernel	= cl::Kernel(program, "GenerateRaysFromWorldMatrix");
		cl::Kernel synthesisDataComputerKernel	= cl::Kernel(program, "ComputeSynthesisData");
		cl::Kernel imageSynthetizerKernel		= cl::Kernel(program, "SynthetizeImage");
        
		// Command queue
		cl::CommandQueue queue = cl::CommandQueue(context, device);

        // Pass the materials of the scene to CL
        cl::Buffer materialBuffer = this->impl->createBuffer(context, materialLibrary);

		// Finish off the impl
		this->impl->platform = platform;
		this->impl->device = device;
		this->impl->context = context;
		this->impl->program = program;
        
		this->impl->localTransformBuffer = cl::Buffer(context, CL_MEM_READ_WRITE, 2*sizeof(Matrix4f), nullptr);

        this->impl->clearSynthBufferKernel = clearSynthBufferKernel;
        this->impl->rayGeneratorKernel = rayGeneratorKernel;
		this->impl->rayGeneratorFromMatrixKernel = rayGeneratorFromMatrixKernel;
        this->impl->synthesisDataComputerKernel = synthesisDataComputerKernel;
        this->impl->imageSynthetizerKernel = imageSynthetizerKernel;
		this->impl->queue = queue;
		this->impl->samplesBuffer = samplesBuffer;
        this->impl->materialLibrary = materialLibrary;

		//if (sampler) {
		//	this->samplesCount = sampler->getSampleCount();
		//}

        this->impl->materialBuffer = materialBuffer;

		this->impl->updateStructSizes();

        BOOST_LOG_TRIVIAL(trace) << "Binding GL texture to the hardware-accelerated ray tracer ...";
        this->impl->setRenderTarget(renderTarget);

        BOOST_LOG_TRIVIAL(trace) << "[Host] Vertex structure size: " << sizeof(Vertex);
		BOOST_LOG_TRIVIAL(trace) << "Ray structure size: " << this->impl->raySize;
		BOOST_LOG_TRIVIAL(trace) << "SynthesisBuffer structure size: " << this->impl->synthesisElementSize;
		
		BOOST_LOG_TRIVIAL(trace) << "Multi-Object ray tracer initialization done.";
    }

    HardwareRenderer::~HardwareRenderer() {}

    void HardwareRenderer::setTransform(const Matrix4f &transform) {
        this->impl->setTransform(transform);
    }

    void HardwareRenderer::renderNodeData(const SceneNodeData *data) {
        this->impl->computeSynthesisBuffer(data);
    }

    void HardwareRenderer::prepareCamera(const Camera *camera) {
        this->impl->generateRays(camera);
    }

    void HardwareRenderer::beginFrame(const Vector4f &color) {
        this->impl->clearSynthesisBuffer();
    }

    void HardwareRenderer::endFrame() {
        this->impl->computeImage();
    }
}}}
