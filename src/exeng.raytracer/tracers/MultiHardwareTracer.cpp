/**
* @file HardwareTracer.hpp
* @brief Interfaz del objeto trazador de rayos
*/

// #define __CL_ENABLE_EXCEPTIONS
#define CL_USE_DEPRECATED_OPENCL_1_1_APIS 

#include "MultiHardwareTracer.hpp"

#include <ostream>
#include <fstream>
#include <list>
#include <iomanip>

#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>

#include <CL/cl.h>
#include <CL/cl_gl.h>

#undef CL_VERSION_1_2
#include <CL/cl.hpp>
#include <GLFW/glfw3.h>

#if defined (EXENG_UNIX)
#  include <GL/glx.h>
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

        cl::Kernel clearSynthBufferKernel;
		cl::Kernel rayGeneratorKernel;
		cl::Kernel synthesisDataComputerKernel;
		cl::Kernel imageSynthetizerKernel;
        
        std::vector<Ray> raysData;

		cl::Buffer raysBuffer;
		cl::Buffer synthesisBuffer;

		cl::Buffer samplesBuffer;
		cl::CommandQueue queue;

		cl_int samplesCount;

		cl::NDRange localSize = cl::NDRange(2, 2);
	};

    struct SynthesisElement {
        float	    distance;	// Distance from the origin of the ray.
        Vector3f    normal;		// Normal vector of the surface that collided with the ray.
        Vector3f    point;		// Point of intersection
        int		    material;	// Material index/id (will be defined later).
    };

    static std::string clErrorToString(cl_int errCode) {
        switch (errCode) {
            case CL_SUCCESS                                  :   return "CL_SUCCESS";
            case CL_DEVICE_NOT_FOUND                         :   return "CL_DEVICE_NOT_FOUND";
            case CL_DEVICE_NOT_AVAILABLE                     :   return "CL_DEVICE_NOT_AVAILABLE";
            case CL_COMPILER_NOT_AVAILABLE                   :   return "CL_COMPILER_NOT_AVAILABLE";
            case CL_MEM_OBJECT_ALLOCATION_FAILURE            :   return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
            case CL_OUT_OF_RESOURCES                         :   return "CL_OUT_OF_RESOURCES";
            case CL_OUT_OF_HOST_MEMORY                       :   return "CL_OUT_OF_HOST_MEMORY";
            case CL_PROFILING_INFO_NOT_AVAILABLE             :   return "CL_PROFILING_INFO_NOT_AVAILABLE";
            case CL_MEM_COPY_OVERLAP                         :   return "CL_MEM_COPY_OVERLAP";
            case CL_IMAGE_FORMAT_MISMATCH                    :   return "CL_IMAGE_FORMAT_MISMATCH";
            case CL_IMAGE_FORMAT_NOT_SUPPORTED               :   return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
            case CL_BUILD_PROGRAM_FAILURE                    :   return "CL_BUILD_PROGRAM_FAILURE";
            case CL_MAP_FAILURE                              :   return "CL_MAP_FAILURE";
            case CL_MISALIGNED_SUB_BUFFER_OFFSET             :   return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
            case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST :   return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
            // case CL_COMPILE_PROGRAM_FAILURE                  :   return "CL_COMPILE_PROGRAM_FAILURE";
            // case CL_LINKER_NOT_AVAILABLE                     :   return "CL_LINKER_NOT_AVAILABLE";
            // case CL_LINK_PROGRAM_FAILURE                     :   return "CL_LINK_PROGRAM_FAILURE";
            // case CL_DEVICE_PARTITION_FAILED                  :   return "CL_DEVICE_PARTITION_FAILED";
            // case CL_KERNEL_ARG_INFO_NOT_AVAILABLE            :   return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";
            case CL_INVALID_VALUE                            :   return "CL_INVALID_VALUE";
            case CL_INVALID_DEVICE_TYPE                      :   return "CL_INVALID_DEVICE_TYPE";
            case CL_INVALID_PLATFORM                         :   return "CL_INVALID_PLATFORM";
            case CL_INVALID_DEVICE                           :   return "CL_INVALID_DEVICE";
            case CL_INVALID_CONTEXT                          :   return "CL_INVALID_CONTEXT";
            case CL_INVALID_QUEUE_PROPERTIES                 :   return "CL_INVALID_QUEUE_PROPERTIES";
            case CL_INVALID_COMMAND_QUEUE                    :   return "CL_INVALID_COMMAND_QUEUE";
            case CL_INVALID_HOST_PTR                         :   return "CL_INVALID_HOST_PTR";
            case CL_INVALID_MEM_OBJECT                       :   return "CL_INVALID_MEM_OBJECT";
            case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR          :   return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
            case CL_INVALID_IMAGE_SIZE                       :   return "CL_INVALID_IMAGE_SIZE";
            case CL_INVALID_SAMPLER                          :   return "CL_INVALID_SAMPLER";
            case CL_INVALID_BINARY                           :   return "CL_INVALID_BINARY";
            case CL_INVALID_BUILD_OPTIONS                    :   return "CL_INVALID_BUILD_OPTIONS";
            case CL_INVALID_PROGRAM                          :   return "CL_INVALID_PROGRAM";
            case CL_INVALID_PROGRAM_EXECUTABLE               :   return "CL_INVALID_PROGRAM_EXECUTABLE";
            case CL_INVALID_KERNEL_NAME                      :   return "CL_INVALID_KERNEL_NAME";
            case CL_INVALID_KERNEL_DEFINITION                :   return "CL_INVALID_KERNEL_DEFINITION";
            case CL_INVALID_KERNEL                           :   return "CL_INVALID_KERNEL";
            case CL_INVALID_ARG_INDEX                        :   return "CL_INVALID_ARG_INDEX";
            case CL_INVALID_ARG_VALUE                        :   return "CL_INVALID_ARG_VALUE";
            case CL_INVALID_ARG_SIZE                         :   return "CL_INVALID_ARG_SIZE";
            case CL_INVALID_KERNEL_ARGS                      :   return "CL_INVALID_KERNEL_ARGS";
            case CL_INVALID_WORK_DIMENSION                   :   return "CL_INVALID_WORK_DIMENSION";
            case CL_INVALID_WORK_GROUP_SIZE                  :   return "CL_INVALID_WORK_GROUP_SIZE";
            case CL_INVALID_WORK_ITEM_SIZE                   :   return "CL_INVALID_WORK_ITEM_SIZE";
            case CL_INVALID_GLOBAL_OFFSET                    :   return "CL_INVALID_GLOBAL_OFFSET";
            case CL_INVALID_EVENT_WAIT_LIST                  :   return "CL_INVALID_EVENT_WAIT_LIST";
            case CL_INVALID_EVENT                            :   return "CL_INVALID_EVENT";
            case CL_INVALID_OPERATION                        :   return "CL_INVALID_OPERATION";
            case CL_INVALID_GL_OBJECT                        :   return "CL_INVALID_GL_OBJECT";
            case CL_INVALID_BUFFER_SIZE                      :   return "CL_INVALID_BUFFER_SIZE";
            case CL_INVALID_MIP_LEVEL                        :   return "CL_INVALID_MIP_LEVEL";
            case CL_INVALID_GLOBAL_WORK_SIZE                 :   return "CL_INVALID_GLOBAL_WORK_SIZE";
            case CL_INVALID_PROPERTY                         :   return "CL_INVALID_PROPERTY";
            // case CL_INVALID_IMAGE_DESCRIPTOR                 :   return "CL_INVALID_IMAGE_DESCRIPTOR";
            // case CL_INVALID_COMPILER_OPTIONS                 :   return "CL_INVALID_COMPILER_OPTIONS";
            // case CL_INVALID_LINKER_OPTIONS                   :   return "CL_INVALID_LINKER_OPTIONS";
            // case CL_INVALID_DEVICE_PARTITION_COUNT           :   return "CL_INVALID_DEVICE_PARTITION_COUNT";
            default: return "UNKNOWN CODE";
        }
    }

    static Vector2i indexToCoord(int index, int width, int height) {
        Vector2i coord;

        coord.x = index % width;
        coord.y = index / height;

        return coord;
    }

    static std::ostream& operator<<(std::ostream &os, const Vector3f& v) {
        os << std::fixed << std::setw( 11 ) << std::setprecision(6) << v.x << ", " << v.y << ", " << v.z;

        return os;
    }

	/*
    void write(std::ostream &os, int width, int height, const std::vector<SynthesisElement>& synthBuffer) {
        for (int i=0; i<synthBuffer.size(); ++i) {
            const SynthesisElement &synthElement = synthBuffer[i];

            os  << "[" << indexToCoord(i, width, height) << "]";
            os  << "Synth {" 
                << "distance:" << synthElement.distance << ", "
                << "normal:" << synthElement.normal << ", "
                << "point:" << synthElement.point
                << "}" 
                << std::endl;
        }
    }

    void write(std::ostream &os, int width, int height, const std::vector<Ray>& rays) {
        for (int i=0; i<rays.size(); ++i) {
            const Ray &ray = rays[i];

            os  << "[" << indexToCoord(i, width, height) << "]";
            os  << "Ray   {" 
                << "point:" << ray.getPoint()  << ", "
                << "direction:" << ray.getDirection() 
                << "}" 
                << std::endl;
        }
    }
	*/
    
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

		BOOST_LOG_TRIVIAL(trace) << "Initializing Multi-Object ray tracer ...";

		std::vector<cl::Platform> platforms;
		cl::Platform::get(&platforms);

		if (platforms.size() == 0) {
			throw std::runtime_error("HardwareTracer::HardwareTracer: No OpenCL platforms available");
		}

		BOOST_LOG_TRIVIAL(trace) << "Found " << platforms.size() << " platform(s).";

		// Select the first platform
		cl::Platform platform = platforms[0];
		BOOST_LOG_TRIVIAL(trace) << "Using OpenCL platform: " << platform.getInfo<CL_PLATFORM_NAME>(nullptr);

		// Select the first GPU device of the first platform.
		std::vector<cl::Device> devices;
		platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
		if (devices.size() == 0) {
			throw std::runtime_error("HardwareTracer::HardwareTracer: No OpenCL GPU devices available");
		}

		BOOST_LOG_TRIVIAL(trace) << "Found " << devices.size() << " device(s).";

		cl::Device device = devices[0];

		BOOST_LOG_TRIVIAL(trace) << "Using OpenCL device: " << device.getInfo<CL_DEVICE_NAME>(nullptr);
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
		cl::Context context = cl::Context({device}, properties);

		// pass the samples to OpenCL
		BOOST_LOG_TRIVIAL(trace) << "Creating sampling buffer from " << sampler->getSampleCount() << " sample(s)...";
		size_t bufferSize = sizeof(Vector2f) * sampler->getSampleCount();
		cl_mem_flags bufferFlags = CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR;
		void* bufferData = (void*)(sampler->getSampleData());

		cl::Buffer samplesBuffer = cl::Buffer(context, bufferFlags, bufferSize, bufferData);

		// Create a Program object from all the kernels
		std::list<std::string> sourceFiles = {
			/*
			getRootPath() + "kernels/Common.cl",
            getRootPath() + "kernels/GenerateRays.cl",
			getRootPath() + "kernels/ComputeSynthesisData.cl",
			getRootPath() + "kernels/SynthetizeImage.cl"
			*/
			getRootPath() + "kernels/MultiHardwareTracer.cl"
		};
		
		BOOST_LOG_TRIVIAL(trace) << "Compiling the following OpenCL C source files ...";

		std::list<std::string> programSourceList;

		for (std::string &source : sourceFiles) {
			BOOST_LOG_TRIVIAL(trace) << source;
			programSourceList.push_back(loadFile(source));
		}

		cl::Program::Sources programSources;
		for (std::string &src : programSourceList) {
			programSources.push_back({src.c_str(), src.size()});
		}

		// Compile the OpenCL programs
		std::string programOptions = "";
		programOptions += "-Werror -g -s";
		programOptions += "\"" + getRootPath() + "kernels/MultiHardwareTracer.cl\"";
		
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
		cl::Kernel synthesisDataComputerKernel	= cl::Kernel(program, "ComputeSynthesisData");
		cl::Kernel imageSynthetizerKernel		= cl::Kernel(program, "SynthetizeImage");
        
		// Command queue
		cl::CommandQueue queue = cl::CommandQueue(context, device);

		// Finish off the impl
		this->impl->platform = platform;
		this->impl->device = device;
		this->impl->context = context;
		this->impl->program = program;
        
        this->impl->clearSynthBufferKernel = clearSynthBufferKernel;
        this->impl->rayGeneratorKernel = rayGeneratorKernel;
        this->impl->synthesisDataComputerKernel = synthesisDataComputerKernel;
        this->impl->imageSynthetizerKernel = imageSynthetizerKernel;
		this->impl->queue = queue;
		this->impl->samplesBuffer = samplesBuffer;
		this->impl->samplesCount = sampler->getSampleCount();

		BOOST_LOG_TRIVIAL(trace) << "Multi-Object ray tracer initialization done.";
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
        Vector3i size = renderTarget->getSize();

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
		BOOST_LOG_TRIVIAL(trace) << "[2] Invoking generateRays kernel with params: "
			<< "Pos={" << camera->getPosition() << "}, "
			<< "LookAt={" << camera->getLookAt() << "}, "
			<< "Up={" << camera->getUp() << "}, "
			<< "Screen= {" << this->getRenderTarget()->getSize() << "}";
		
        // std::ofstream fs;
        // fs.open("C:/rays.txt", std::ios_base::app);
        cl_int errCode = 0;
        cl::Event event;

        // Prepare the 'GenerateRays' kernel
        cl::Kernel &kernel = this->impl->rayGeneratorKernel;

        Vector3f pos = camera->getPosition(); 
        Vector3f lookAt = camera->getLookAt(); 
        Vector3f up = camera->getUp();
        Vector3i size = this->getRenderTarget()->getSize();

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
        errCode = this->impl->queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(size.x, size.y), this->impl->localSize, nullptr, &event);
        if (errCode != CL_SUCCESS) {
			std::string msg = "MultiHardwareTracer::generateRays: Error at trying to enqueue the GenerateRays Kernel:" + clErrorToString(errCode);
			BOOST_LOG_TRIVIAL(error) << msg;

            throw std::runtime_error(msg);
        }
        event.wait();

        // for debugging
		/*
        this->impl->raysData.resize(size.x * size.y);
        errCode = this->impl->queue.enqueueReadBuffer(this->impl->raysBuffer, CL_TRUE, 0, this->impl->raysData.size()*sizeof(Ray), this->impl->raysData.data());
        if (errCode != CL_SUCCESS) {
            throw std::runtime_error("MultiHardwareTracer::generateRays: Error at trying to enqueue the GenerateRays Kernel:" + clErrorToString(errCode));
        }
        event.wait();

        write(fs, size.x, size.y, this->impl->raysData);
        fs << std::endl;
		*/

        this->impl->queue.finish();
	}

    static void linearizeSceneBranch(std::list<const SceneNode*> &nodes, const SceneNode *node) {
        if (node == nullptr) {
            return;
        }

        if (node->getData()==nullptr) {
            if (node->getChildCount() > 0) {
                for (SceneNode *childNode : node->getChilds()) {
                    linearizeSceneBranch(nodes, childNode);
                }
            }

            return;
        }

        if (node->getData()->getTypeInfo()==TypeId<Mesh>()) {
            nodes.push_back(node);
        }
    }
    
    std::list<const SceneNode*> getSceneNodes(const Scene *scene) {
        std::list<const SceneNode*> nodes;

        linearizeSceneBranch(nodes, scene->getRootNode());

        return nodes;
    }

    void MultiHardwareTracer::clearSynthBuffer() {
		BOOST_LOG_TRIVIAL(trace) << "[1] Invoking clearSyntBuffer kernel with params: ScreenSize={" << this->getRenderTarget()->getSize() << "}";

        cl_int errCode = 0;
        cl::Event event;
        cl::CommandQueue &queue = this->impl->queue;
        cl::Kernel &kernel = this->impl->clearSynthBufferKernel;
        
        Vector3i size = this->getRenderTarget()->getSize();
        
        kernel.setArg(0, this->impl->synthesisBuffer);
        kernel.setArg(1, size.x);
        kernel.setArg(2, size.y);

        errCode = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(size.x, size.y), cl::NullRange, nullptr, &event);
        if (errCode != CL_SUCCESS) {
			std::string msg = "MultiHardwareTracer::clearSynthBuffer: Error at trying to execute the ClearSynthBuffer kernel:" + clErrorToString(errCode);
			BOOST_LOG_TRIVIAL(error) << msg;

            throw std::runtime_error(msg);
        }
        
        event.wait();
    }
    
	void MultiHardwareTracer::computeSynthesisData() {
        // std::ofstream fs;
        // fs.open("C:/synth.txt", std::ios_base::app);
        std::list<const SceneNode*> nodes = getSceneNodes(this->getScene());
        
        // Invoke the ComputeSynthesisData kernel
        Vector2i screenSize = this->getRenderTarget()->getSize();

        cl_int errCode = 0;

        cl::Event event;
        cl::Kernel &kernel = this->impl->synthesisDataComputerKernel;

        for (const SceneNode* node : nodes) {
            Mesh *mesh = static_cast<Mesh*>(node->getData());

            for (int i=0; i<mesh->getMeshSubsetCount(); ++i) {
                // Prepare the kernel for execution
                MeshSubset *subset = mesh->getMeshSubset(i);

                GLuint vertexBufferId = static_cast<GLuint>(subset->getBuffer(0)->getHandle());
                GLuint indexBufferId = static_cast<GLuint>(subset->getIndexBuffer()->getHandle());
                
                cl::BufferGL vertexBuffer = cl::BufferGL(this->impl->context, CL_MEM_READ_WRITE, vertexBufferId);
                cl::BufferGL indexBuffer = cl::BufferGL(this->impl->context, CL_MEM_READ_WRITE, indexBufferId);

                int indexFormatSize = IndexFormat::getSize(subset->getIndexFormat());
                int indexCount = subset->getIndexBuffer()->getSize() / indexFormatSize;

				BOOST_LOG_TRIVIAL(trace) 
					<< "[3] Invoking computeSynthesisData kernel with params: "
					<< "ScreenSize={" << screenSize << "}, "
					<< "TriangleCount=" << indexCount;

                kernel.setArg(0, this->impl->synthesisBuffer);
                kernel.setArg(1, this->impl->raysBuffer);
                kernel.setArg(2, screenSize.x);
                kernel.setArg(3, screenSize.y);
                kernel.setArg(4, vertexBuffer);
                kernel.setArg(5, indexBuffer);
                kernel.setArg(6, indexCount);
                kernel.setArg(7, 1);

                std::vector<cl::Memory> buffers = {vertexBuffer, indexBuffer};

                cl::CommandQueue &queue = this->impl->queue;

                errCode = queue.enqueueAcquireGLObjects(&buffers, nullptr, &event);
                if (errCode != CL_SUCCESS) {
					std::string msg = "MultiHardwareTracer::computeSynthesisData: Error at trying to acquire the GL buffer object:" + clErrorToString(errCode);
					BOOST_LOG_TRIVIAL(error) << msg;

                    throw std::runtime_error(msg);
                }
                event.wait();
                
                errCode = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(screenSize.x, screenSize.y), this->impl->localSize, nullptr, &event);
                if (errCode != CL_SUCCESS) {
					std::string msg = "MultiHardwareTracer::computeSynthesisData: Error at trying to execute the ComputeSynthesisBuffer kernel:" + clErrorToString(errCode);
					BOOST_LOG_TRIVIAL(error) << msg;
                    throw std::runtime_error(msg);
                }
                event.wait();

                errCode = queue.enqueueReleaseGLObjects(&buffers, nullptr, &event);
                if (errCode != CL_SUCCESS) {
					std::string msg = "MultiHardwareTracer::computeSynthesisData: Error at trying to release the GL buffer object:" + clErrorToString(errCode);
					BOOST_LOG_TRIVIAL(error) << msg;
                    throw std::runtime_error(msg);
                }
                event.wait();

				/*
                std::vector<SynthesisElement> synthData;
                synthData.resize(screenSize.x * screenSize.y);
                errCode = queue.enqueueReadBuffer(this->impl->synthesisBuffer, CL_TRUE, 0, synthData.size()*sizeof(SynthesisElement), synthData.data(), nullptr, &event);
                if (errCode != CL_SUCCESS) {
                    throw std::runtime_error("MultiHardwareTracer::computeSynthesisData: Error at trying readback the synthesis buffer:" + clErrorToString(errCode));
                }
                event.wait();

                write(fs, screenSize.x, screenSize.y, synthData);
                fs << std::endl;
				*/

                queue.finish();
            }
        }
	}

	void MultiHardwareTracer::synthetizeImage() {
        Vector3i size = this->getRenderTarget()->getSize();
        cl::Event event;
        cl::Kernel &kernel = this->impl->imageSynthetizerKernel;
        cl_int errCode = 0;

        kernel.setArg(0, this->impl->image);
        kernel.setArg(1, this->impl->synthesisBuffer);
        kernel.setArg(2, this->impl->raysBuffer);
        kernel.setArg(3, size.x);
        kernel.setArg(4, size.y);

        cl::CommandQueue &queue = this->impl->queue;

        std::vector<cl::Memory> buffers = {this->impl->image};

		BOOST_LOG_TRIVIAL(trace) 
			<< "[4] Invoking synthetizeImage kernel with params: "
			<< "ScreenSize={" << size << "}";
		
        errCode = queue.enqueueAcquireGLObjects(&buffers, nullptr, &event);
        if (errCode != CL_SUCCESS) {
			std::string msg = "MultiHardwareTracer::synthetizeImage: Error at trying to acquire the GL texture object: " + clErrorToString(errCode);

			BOOST_LOG_TRIVIAL(trace) << msg;
            throw std::runtime_error(msg);
        }
        event.wait();

        errCode = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(size.x, size.y), this->impl->localSize, nullptr, &event);
        if (errCode != CL_SUCCESS) {
			std::string msg = "MultiHardwareTracer::synthetizeImage: Error at trying to enqueue the SynthetizeImage kernel: " + clErrorToString(errCode);

			BOOST_LOG_TRIVIAL(trace) << msg;
            throw std::runtime_error(msg);
        }
        event.wait();

        errCode = queue.enqueueReleaseGLObjects(&buffers, nullptr, &event);
        if (errCode != CL_SUCCESS) {
			std::string msg = "MultiHardwareTracer::synthetizeImage: Error at trying to release the GL texture object:" + clErrorToString(errCode);

			BOOST_LOG_TRIVIAL(trace) << msg;
            throw std::runtime_error(msg);
        }
        event.wait();

        queue.finish();
	}
    
	void MultiHardwareTracer::render(const exeng::scenegraph::Camera *camera) {
		BOOST_LOG_TRIVIAL(trace) << "Rendering scene ...";

        this->clearSynthBuffer();
        this->generateRays(camera);
        this->computeSynthesisData();
        this->synthetizeImage();
	}
}}
