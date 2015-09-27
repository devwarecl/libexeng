
#include "HardwareRendererPrivate.hpp"

#include <ostream>
#include <fstream>
#include <iomanip>
#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>
#include <exeng/Exception.hpp>
#include <exeng/scenegraph/Mesh.hpp>

namespace exeng { namespace raytracer { namespace renderers {

    using namespace exeng::graphics;
    using namespace exeng::scenegraph;

    struct SynthesisElement {
		cl_float3	point;		// Point of intersection
        cl_float3	normal;		// Normal vector of the surface that collided with the ray.
		cl_float	distance;	// Distance from the origin of the ray.
        cl_int		material;	// Material index/id (will be defined later).
    };
	
	const int MaterialSize = 4;	// Size of the material (number of float's)

    std::string HardwareRendererPrivate::clErrorToString(cl_int errCode) {
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
            // case CL_INVALID_PROPERTY                         :   return "CL_INVALID_PROPERTY";
            // case CL_INVALID_IMAGE_DESCRIPTOR                 :   return "CL_INVALID_IMAGE_DESCRIPTOR";
            // case CL_INVALID_COMPILER_OPTIONS                 :   return "CL_INVALID_COMPILER_OPTIONS";
            // case CL_INVALID_LINKER_OPTIONS                   :   return "CL_INVALID_LINKER_OPTIONS";
            // case CL_INVALID_DEVICE_PARTITION_COUNT           :   return "CL_INVALID_DEVICE_PARTITION_COUNT";
            default: EXENG_THROW_EXCEPTION("clErrorToString: Unknown error code " + std::to_string(errCode) + ".");
        }
    }

    Vector2i HardwareRendererPrivate::indexToCoord(int index, int width, int height) {
        Vector2i coord = {
			index / height,
			index % width
		};

        return coord;
    }

    cl::Buffer HardwareRendererPrivate::createBuffer(cl::Context &context, const MaterialLibrary *library) {
        cl::Buffer materialBuffer;

        if (library->getMaterialCount() > 0) {
			const int MaterialStride = MaterialSize * 4;
            const int MaterialBufferSize = library->getMaterialCount() * MaterialStride;

			std::vector<Vector4f> materialData(library->getMaterialCount());

            for (int i=0; i<library->getMaterialCount(); ++i) {
                const Material *material = library->getMaterial(i);

                Vector4f color;
                    
                if (material) {
                    color = library->getMaterial(i)->getAttribute<Vector4f>("diffuse");
                } else {
                    color = {1.0f, 1.0f, 1.0f, 1.0f};
                    BOOST_LOG_TRIVIAL(trace) << "Material " << i << " is null.";
                }

			    materialData[i] = color;
            }

            cl_mem_flags bufferFlags = CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR;
            materialBuffer = cl::Buffer(context, bufferFlags, MaterialBufferSize, materialData.data());
        } 
        
        return materialBuffer;
    }

    void HardwareRendererPrivate::setRenderTarget(exeng::graphics::Texture *renderTarget) {
		// Create a OpenCL 2D image  from the render target Texture
		GLuint textureId = static_cast<GLuint>(renderTarget->getHandle());
		if (textureId <= 0) {
			throw std::runtime_error("Invalid render target texture id (non positive)");
		}

		cl_int errorCode = 0;

		cl::Image2DGL image(this->context, CL_MEM_WRITE_ONLY, GL_TEXTURE_2D, 0, textureId, &errorCode);
		if (errorCode != CL_SUCCESS) {
			std::string str;
			str += "HardwareTracer::setRenderTarget: Invalid render target texture. Error code: ";
			str += boost::lexical_cast<std::string>(errorCode);

			throw std::runtime_error(str);
		}
		
        // Create the CL buffers for the intermediate data
        Vector3i size = renderTarget->getSize();

        // this->raysData.resize(size.x*size.y);
		const int synthesisBufferSize = size.x*size.y*this->synthesisElementSize;
		const int raysBufferSize = size.x*size.y*this->raySize;

        cl::Buffer synthesisBuffer = cl::Buffer(this->context, CL_MEM_READ_WRITE, synthesisBufferSize);
		cl::Buffer raysBuffer = cl::Buffer(this->context, CL_MEM_READ_WRITE, raysBufferSize);

		this->image = image;
        this->synthesisBuffer = synthesisBuffer;
		this->raysBuffer = raysBuffer;
        this->renderTarget = renderTarget;
	}

    void HardwareRendererPrivate::generateRays(const exeng::scenegraph::Camera *camera) {
		BOOST_LOG_TRIVIAL(trace) << "[2] Invoking generateRays kernel with params: "
			<< "Pos={" << camera->getPosition() << "}, "
			<< "LookAt={" << camera->getLookAt() << "}, "
			<< "Up={" << camera->getUp() << "}, "
			<< "Screen= {" << this->renderTarget->getSize() << "}";
		
        // std::ofstream fs;
        // fs.open("C:/rays.txt", std::ios_base::out);
        
        cl_int errCode = 0;
        cl::Event event;

        // Prepare the 'GenerateRays' kernel
        cl::Kernel &kernel = this->rayGeneratorKernel;

        Vector3f pos = camera->getPosition(); 
        Vector3f lookAt = camera->getLookAt(); 
        Vector3f up = camera->getUp();
        Vector3i size = this->renderTarget->getSize();
		
        kernel.setArg(0, this->raysBuffer);
        
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
        errCode = this->queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(size.x, size.y), this->localSize, nullptr, &event);
        if (errCode != CL_SUCCESS) {
			std::string msg = "MultiHardwareTracer::generateRays: Error at trying to enqueue the GenerateRays Kernel:" + clErrorToString(errCode);
			BOOST_LOG_TRIVIAL(error) << msg;

            throw std::runtime_error(msg);
        }
        event.wait();
		
        this->queue.finish();
	}

    void HardwareRendererPrivate::clearSynthesisBuffer() {
		BOOST_LOG_TRIVIAL(trace) << "[1] Invoking clearSyntBuffer kernel with params: ScreenSize={" << this->renderTarget->getSize() << "}";

        cl_int errCode = 0;
        cl::Event event;
        cl::CommandQueue &queue = this->queue;
        cl::Kernel &kernel = this->clearSynthBufferKernel;
        
        Vector3i size = this->renderTarget->getSize();
        
        kernel.setArg(0, this->synthesisBuffer);
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
    
	void HardwareRendererPrivate::computeSynthesisBuffer(const SceneNodeData *nodeData) {
		// std::ofstream fs;
		// fs.open("C:/synth.txt", std::ios_base::out);
		// std::list<const SceneNode*> nodes = getSceneNodes(this->getScene());
        
		// Invoke the ComputeSynthesisData kernel
		Vector2i screenSize = this->renderTarget->getSize();

		cl_int errCode = 0;

		cl::Event event;
		cl::Kernel &kernel = this->synthesisDataComputerKernel;

		const Mesh *mesh = static_cast<const Mesh*>(nodeData);

		for (int i=0; i<mesh->getSubsetCount(); ++i) {
			// Prepare the kernel for execution
			const MeshSubset *subset = mesh->getSubset(i);

			const GLuint vertexBufferId = static_cast<GLuint>(subset->getBuffer(0)->getHandle());
			const GLuint indexBufferId = static_cast<GLuint>(subset->getIndexBuffer()->getHandle());
                
			cl::BufferGL vertexBuffer = cl::BufferGL(this->context, CL_MEM_READ_WRITE, vertexBufferId);
			cl::BufferGL indexBuffer = cl::BufferGL(this->context, CL_MEM_READ_WRITE, indexBufferId);

			const int indexCount = subset->getIndexCount();
            const int materialIndex = this->materialLibrary->getMaterialIndex(subset->getMaterial());

			BOOST_LOG_TRIVIAL(trace) 
				<< "[3] Invoking computeSynthesisData kernel with params: "
				<< "ScreenSize={" << screenSize << "}, "
				<< "TriangleCount=" << indexCount;

			kernel.setArg(0, this->synthesisBuffer);
			kernel.setArg(1, this->raysBuffer);
			kernel.setArg(2, screenSize.x);
			kernel.setArg(3, screenSize.y);
			kernel.setArg(4, vertexBuffer);
			kernel.setArg(5, indexBuffer);
			kernel.setArg(6, indexCount);
			kernel.setArg(7, materialIndex);
			kernel.setArg(8, this->localTransformBuffer);
                
			std::vector<cl::Memory> buffers = {vertexBuffer, indexBuffer};
                
			cl::CommandQueue &queue = this->queue;

			errCode = queue.enqueueAcquireGLObjects(&buffers, nullptr, &event);
			if (errCode != CL_SUCCESS) {
				std::string msg = "MultiHardwareTracer::computeSynthesisData: Error at trying to acquire the GL buffer object:" + clErrorToString(errCode);
				BOOST_LOG_TRIVIAL(error) << msg;

				throw std::runtime_error(msg);
			}
			event.wait();
                
			errCode = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(screenSize.x, screenSize.y), this->localSize, nullptr, &event);
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

			queue.finish();
		}
	}

	void HardwareRendererPrivate::computeImage() {
        Vector3i size = this->renderTarget->getSize();
        cl::Event event;
        cl::Kernel &kernel = this->imageSynthetizerKernel;
        cl_int errCode = 0;

        kernel.setArg(0, this->image);
        kernel.setArg(1, this->synthesisBuffer);
        kernel.setArg(2, this->raysBuffer);
        kernel.setArg(3, size.x);
        kernel.setArg(4, size.y);
		kernel.setArg(5, MaterialSize);
		kernel.setArg(6, this->materialBuffer);

        cl::CommandQueue &queue = this->queue;

        std::vector<cl::Memory> buffers = {this->image};

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

        errCode = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(size.x, size.y), this->localSize, nullptr, &event);
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

    void HardwareRendererPrivate::updateStructSizes() {
		const int StructuresCount = 3;
		cl_int out[StructuresCount] = {0};

		cl::Event event;
		cl::CommandQueue &queue = this->queue;
		cl::Kernel kernel = cl::Kernel(this->program, "GetStructuresSize");
		cl::Buffer outBuffer = cl::Buffer(this->context, CL_MEM_READ_WRITE, sizeof(cl_int)*StructuresCount);

		cl_int errCode;

		kernel.setArg(0, outBuffer);

		errCode = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(1, 1),  cl::NullRange, nullptr, &event);
		if (errCode != CL_SUCCESS) {
			std::string msg = "MultiHardwareTracer::executeGetSynthesisElementSizeKernel: Error :" + clErrorToString(errCode);

			BOOST_LOG_TRIVIAL(trace) << msg;
            throw std::runtime_error(msg);
        }
		event.wait();

		errCode = queue.enqueueReadBuffer(outBuffer, CL_TRUE, 0, sizeof(cl_int)*StructuresCount, out, nullptr, &event);
		if (errCode != CL_SUCCESS) {
			std::string msg = "MultiHardwareTracer::executeGetSynthesisElementSizeKernel: Error :" + clErrorToString(errCode);

			BOOST_LOG_TRIVIAL(trace) << msg;
            throw std::runtime_error(msg);
        }
		event.wait();

		queue.finish();
		
		this->raySize = out[0];
		this->synthesisElementSize = out[1];
	}

    void HardwareRendererPrivate::setTransform(const Matrix4f &localTransform) {
		Matrix4f matrixData[] = {
			localTransform,
			inverse(localTransform)
		};

        const int matrixDataSize = sizeof(matrixData);

        cl::Event event;
		cl_int errCode = this->queue.enqueueWriteBuffer(this->localTransformBuffer, CL_TRUE, 0, matrixDataSize, matrixData, nullptr, &event);
		if (errCode != CL_SUCCESS) {
			std::string msg = "MultiHardwareTracer::executeGetSynthesisElementSizeKernel: Error :" + clErrorToString(errCode);
			BOOST_LOG_TRIVIAL(trace) << msg;
            throw std::runtime_error(msg);
		}
		event.wait();
    }
}}}
