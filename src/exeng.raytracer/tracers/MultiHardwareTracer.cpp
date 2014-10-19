/**
* @file HardwareTracer.hpp
* @brief Interfaz del objeto trazador de rayos
*/

// #define __CL_ENABLE_EXCEPTIONS
#define CL_USE_DEPRECATED_OPENCL_1_1_APIS 

#include <fstream>
#include <list>

#include "MultiHardwareTracer.hpp"

#include <boost/lexical_cast.hpp>
#include <CL/cl.h>
#include <CL/cl_gl.h>

#undef CL_VERSION_1_2
#include <CL/cl.hpp>
#include <GLFW/glfw3.h>

#if defined (EXENG_UNIX)
#include <GL/glx.h>
#endif

using namespace exeng;
using namespace exeng::math;
using namespace exeng::graphics;
using namespace exeng::scenegraph;

namespace raytracer { namespace tracers {
	struct MultiHardwareTracer::Private {

		cl::Platform platform;
		cl::Device device;
		cl::Context context;

		cl::Program program;
		cl::Image2DGL image;

		cl::Kernel rayGeneratorKernel;
		cl::Kernel synthesisDataComputerKernel;
		cl::Kernel imageSynthetizerKernel;

        std::vector<Ray> raysData;

		cl::Buffer raysBuffer;
		cl::Buffer synthesisBuffer;

		cl::Buffer samplesBuffer;
		cl::CommandQueue queue;

		cl_int samplesCount;
	};

    struct SynthesisElement {
        float	    distance;	// Distance from the origin of the ray.
        Vector3f    normal;		// Normal vector of the surface that collided with the ray.
        Vector3f    point;		// Point of intersection
        int		    material;	// Material index/id (will be defined later).
    };

	static std::string getRootPath() {
		return std::string(RAYTRACER_ROOT_FOLDER);
	}

	static std::string loadFile(const std::string &file) {
		std::ifstream fs;
		fs.open(file.c_str(), std::ios_base::in);

		if (!fs.is_open()) {
			throw std::runtime_error("loadFile: File '" + file + "' couldn't be loaded.");
		}

		std::string content;
		std::string line;

		while (!fs.eof()) {
			std::getline(fs, line);
			content += line + "\n";
		}

		return content;
	}

	//static cl::Buffer createCLBuffer(cl::Context &context, exeng::Buffer *in) {
	//	if (in == nullptr) {
	//		throw std::runtime_error("[HardwareTracer.cpp] createCLBuffer -> The input buffer can't be a nullptr.");
	//	}
	//	cl_int errCode = 0;
	//	cl::Buffer result /*= cl::Buffer(context, , in->getSize(), in->getDataPtr())*/;
	//	return result;
	//}

	MultiHardwareTracer::MultiHardwareTracer(const Scene *scene, const raytracer::samplers::Sampler *sampler) : Tracer(scene, nullptr), impl(new MultiHardwareTracer::Private())  {
		std::vector<cl::Platform> platforms;
		cl::Platform::get(&platforms);

		if (platforms.size() == 0) {
			throw std::runtime_error("HardwareTracer::HardwareTracer: No OpenCL platforms available");
		}

		// Select the first platform
		cl::Platform platform = platforms[0];

		// Select the first GPU device of the first platform.
		std::vector<cl::Device> devices;
		platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
		if (devices.size() == 0) {
			throw std::runtime_error("HardwareTracer::HardwareTracer: No OpenCL GPU devices available");
		}

		cl::Device device = devices[0];

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
		cl::Context context = cl::Context({ device }, properties);

		// pass the samples to OpenCL
		size_t bufferSize = sizeof(Vector2f) * sampler->getSampleCount();
		cl_mem_flags bufferFlags = CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR;
		void* bufferData = (void*)(sampler->getSampleData());

		cl::Buffer samplesBuffer = cl::Buffer(context, bufferFlags, bufferSize, bufferData);

		// Create a Program object from all the kernels
		std::list<std::string> programSourceList = {
            loadFile(getRootPath() + "kernels/Common.cl"),
            loadFile(getRootPath() + "kernels/GenerateRays.cl"),
			loadFile(getRootPath() + "kernels/ComputeSynthesisData.cl") //,
			// loadFile(getRootPath() + "kernels/TraceRay.cl")
		};

		cl::Program::Sources programSources;
		for (std::string &src : programSourceList) {
			programSources.push_back({src.c_str(), src.size()});
		}

		// Compile the OpenCL programs
		cl::Program program = cl::Program(context, programSources);
		program.build({ device }, "-Werror");
		if (program.build({ device }) != CL_SUCCESS) {
			std::string msg;
			msg += "OpenCL program compile error: ";
			msg += program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);
			msg += "\n";

			throw std::runtime_error(msg);
		}

		cl::Kernel rayGeneratorKernel			= cl::Kernel(program, "GenerateRays");
		cl::Kernel synthesisDataComputerKernel	= cl::Kernel(program, "ComputeSynthesisData");
		// cl::Kernel imageSynthetizerKernel		= cl::Kernel(program, "SynthetizeImage");

		// Command queue
		cl::CommandQueue queue = cl::CommandQueue(context, device);

		// Finish off the impl
		this->impl->platform = platform;
		this->impl->device = device;
		this->impl->context = context;
		this->impl->program = program;
        this->impl->rayGeneratorKernel = rayGeneratorKernel;
        this->impl->synthesisDataComputerKernel = synthesisDataComputerKernel;
        // this->impl->imageSynthetizerKernel = imageSynthetizerKernel;
		this->impl->queue = queue;
		this->impl->samplesBuffer = samplesBuffer;
		this->impl->samplesCount = sampler->getSampleCount();
	}

	void MultiHardwareTracer::setRenderTarget(exeng::graphics::Texture *renderTarget) {

		// Create a OpenCL 2D image  from the render target Texture
		GLuint textureId = static_cast<GLuint>(renderTarget->getHandle());
		if (textureId <= 0) {
			throw std::runtime_error("Invalid render target texture id (non positive)");
		}

		cl_int errorCode = 0;

		cl::Image2DGL image(this->impl->context, CL_MEM_WRITE_ONLY, GL_TEXTURE_2D, 0, textureId, &errorCode);
		if (errorCode != CL_SUCCESS) {
			std::string str;
			str += "HardwareTracer::setRenderTarget: Invalid render target texture. Error code: ";
			str += boost::lexical_cast<std::string>(errorCode);

			throw std::runtime_error(str);
		}

        // Create the CL buffers for the intermediate data
        Vector3i size = renderTarget->geSize();

        this->impl->raysData.resize(size.x*size.y);

        cl::Buffer raysBuffer = cl::Buffer(this->impl->context, CL_MEM_READ_WRITE, size.x*size.y*sizeof(Ray));
        cl::Buffer synthesisBuffer = cl::Buffer(this->impl->context, CL_MEM_READ_WRITE, size.x*size.y*sizeof(SynthesisElement));

		this->impl->image = image;
        this->impl->raysBuffer = raysBuffer;
        this->impl->synthesisBuffer = synthesisBuffer;

		Tracer::setRenderTarget(renderTarget);
	}

	MultiHardwareTracer::~MultiHardwareTracer() {
    }

    void MultiHardwareTracer::generateRays(const exeng::scenegraph::Camera *camera) {
        cl::Event event;

        // Prepare the 'GenerateRays' kernel
        cl::Kernel &kernel = this->impl->rayGeneratorKernel;

        Vector3f pos = camera->getPosition(); 
        Vector3f lookAt = camera->getLookAt(); 
        Vector3f up = camera->getUp();
        Vector3i size = this->getRenderTarget()->geSize();

        kernel.setArg(0, this->impl->raysBuffer);
        
        kernel.setArg(1, pos.x);
        kernel.setArg(2, pos.y);
        kernel.setArg(3, pos.z);

        kernel.setArg(4, lookAt.x);
        kernel.setArg(5, lookAt.y);
        kernel.setArg(6, lookAt.z);

        kernel.setArg(7, up.x);
        kernel.setArg(8, up.y);
        kernel.setArg(9, up.z);

        kernel.setArg(10, size.x);
        kernel.setArg(11, size.y);

        // Execute the kernel
        this->impl->queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(size.x, size.y), cl::NDRange(16, 16), nullptr, &event);
        event.wait();

        this->impl->queue.enqueueReadBuffer(this->impl->raysBuffer, CL_TRUE, 0, this->impl->raysData.size()*sizeof(Ray), this->impl->raysData.data());
        event.wait();

        this->impl->queue.finish();
	}

	void MultiHardwareTracer::computeSynthesisData() {

	}

	void MultiHardwareTracer::synthetizeImage() {

	}

	void MultiHardwareTracer::render(const exeng::scenegraph::Camera *camera) {
        this->generateRays(camera);
	}
}}
