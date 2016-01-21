
/**
 * nVidia Matrix Multiplication Example
 */

#include <iostream>
#include <vector>
#include <random>
#include <cstdint>
#include <memory>
#include <xe/Matrix.hpp>
#include <xe/Timer.hpp>
#include <CL/cl.hpp>

class Timer {
public:
    Timer() {
        this->start = xe::Timer::getTime();
    }
    
    ~Timer() {
        std::cout << xe::Timer::getTime() - start << std::endl;
    }

private:
    std::uint32_t start = 0;
};

class Task {
public:
	virtual ~Task() {}

	virtual void initialize(cl::Device &device, cl::Context &context) = 0;
	virtual void execute(cl::CommandQueue &queue) = 0;

	virtual std::string getName() const = 0;
};
typedef std::unique_ptr<Task> TaskPtr;

class TaskException : public std::runtime_error {
public:
	TaskException(const char *msg) : std::runtime_error(msg) {}
	TaskException(const std::string &msg) : std::runtime_error(msg) {}
};

class TaskExecuter {
public:
	TaskExecuter() {
		cl_int errorCode = 0;

		// Obtener la primera plataforma OpenCL (implementacion de OpenCL)
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);
        cl::Platform platform = platforms[0];
        
        // Obtener el primer dispositivo de OpenCL de tipo GPU
        std::vector<cl::Device> devices;
        cl::Device device;
        platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
        device = devices[0];

        // Create Context
        cl_context_properties properties [] = {
            CL_CONTEXT_PLATFORM, (cl_context_properties) platform(),
            0, 0
        };

        std::vector<cl::Device> selectedDevices = {device};
        
        cl::Context context = cl::Context(selectedDevices, &properties[0], nullptr, nullptr, nullptr);

        // Crear la cola de comandos, que permitira 
        cl::CommandQueue queue(context, device, 0, &errorCode);
        if (errorCode != CL_SUCCESS) {
            throw TaskException(std::to_string(errorCode));
        }

        this->platform = platform;
        this->device = device;
        this->context = context;
        this->queue = queue;

		this->localMemSize = device.getInfo<CL_DEVICE_LOCAL_MEM_SIZE>();
		this->maxWorkgroupSize = device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>();
		this->maxWorkItemSizes = device.getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>();
		this->minDataTypeAlignSize = device.getInfo<CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE>();
	}

	virtual ~TaskExecuter() {}

	void initializeTask(Task *task) {
		task->initialize(this->device, this->context);
	}

	void executeTask(Task *task) {
		std::cout << task->getName() << " ";

		Timer __time1;
		task->execute(this->queue);
	}

private:
	cl::Platform platform;
    cl::Device device;
    cl::Context context;
    cl::CommandQueue queue;

	cl_ulong localMemSize = 0;
	size_t maxWorkgroupSize = 0;
	std::vector<size_t> maxWorkItemSizes;
	size_t minDataTypeAlignSize = 0;
};
typedef std::unique_ptr<TaskExecuter> TaskExecuterPtr;

const int TOTAL_VALUES = 1024*1024*10*2;

class ArrayAddTask : public Task {
public:
	ArrayAddTask() {
		this->kernelSource = R"(
			__kernel
			void Add (
					__global float *out, 
					__global const float *in1, 
					__global const float *in2,
					__local float *cache1,
					__local float *cache2) {
				
				// fill the local memory cache for the current workgroup
				const int globalId = get_global_id(0);
				const int localId = get_local_id(0);

				cache1[localId] = in1[globalId];
				cache2[localId] = in2[globalId];
				
				barrier(CLK_LOCAL_MEM_FENCE);

				const int i = globalId;	

				const float n1 = cache1[localId];
				const float n2 = cache2[localId];
				const float base = (n1 + n2);
				
				out[i] = base*base;
			}
		)";
	}

	virtual ~ArrayAddTask() {}

	virtual std::string getName() const {
		return "Add";
	}

	virtual void initialize(cl::Device &device, cl::Context &context) override {
		cl_int errorCode = 0;

		// Create program sources
		cl::Program::Sources sources = {{kernelSource.c_str(), kernelSource.size() + 1}};
        cl::Program program(context, sources, &errorCode);
        errorCode = program.build({device}, nullptr, nullptr, nullptr);
        if (errorCode != CL_SUCCESS) {
            std::string msg = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) + ".";
            throw TaskException(msg.c_str());
        }

        // Create kernel 
        cl::Kernel kernel(program, "Add", &errorCode);
		if (errorCode != CL_SUCCESS) {
            throw TaskException(std::to_string(errorCode));
        }

		// Prepare buffer data
		std::vector<float> values1(TOTAL_VALUES);
		std::vector<float> values2(TOTAL_VALUES);

		std::generate(std::begin(values1), std::end(values1), std::rand);
		std::generate(std::begin(values2), std::end(values2), std::rand);
		
		cl::Buffer bufferIn1 = cl::Buffer(context, std::begin(values1), std::end(values1), true, true, &errorCode);
		if (errorCode != CL_SUCCESS) {
            throw TaskException(std::to_string(errorCode));
        }

		cl::Buffer bufferIn2 = cl::Buffer(context, std::begin(values2), std::end(values2), true, true, &errorCode);
		if (errorCode != CL_SUCCESS) {
            throw TaskException(std::to_string(errorCode));
        }

		cl::Buffer bufferOut = cl::Buffer(context, CL_MEM_READ_WRITE, sizeof(float)*values1.size(), nullptr, &errorCode);
		if (errorCode != CL_SUCCESS) {
            throw TaskException(std::to_string(errorCode));
        }

		this->kernel = kernel;
		this->program = program;
		this->bufferIn1 = bufferIn1;
		this->bufferIn2 = bufferIn2;
		this->bufferOut = bufferOut;
	}

	virtual void execute(cl::CommandQueue &queue) override {
		cl::Event event;

		cl_int errorCode = 0;

		const int LOCAL_SIZE = 512;

		this->kernel.setArg(0, this->bufferOut);
		this->kernel.setArg(1, this->bufferIn1);
		this->kernel.setArg(2, this->bufferIn2);
		this->kernel.setArg(3, sizeof(float)*LOCAL_SIZE, nullptr);
		this->kernel.setArg(4, sizeof(float)*LOCAL_SIZE, nullptr);

		// errorCode = queue.enqueueNDRangeKernel(this->kernel, cl::NullRange, cl::NDRange(TOTAL_VALUES), cl::NullRange, nullptr, &event);
		errorCode = queue.enqueueNDRangeKernel(this->kernel, cl::NullRange, cl::NDRange(TOTAL_VALUES), cl::NDRange(LOCAL_SIZE), nullptr, &event);
		if (errorCode != CL_SUCCESS) {
            throw TaskException(std::to_string(errorCode));
        }

		errorCode = event.wait();
	}

private:
	cl::Program program;
    cl::Kernel kernel;

	cl::Buffer bufferOut;
	cl::Buffer bufferIn1;
	cl::Buffer bufferIn2;

	std::string kernelSource = "";

	const int LOCA_SIZE = 0;
};

class ArrayAddNativeTask : public Task {
public:
	virtual std::string getName() const {
		return "AddNativeTask";
	}

	virtual void initialize(cl::Device &device, cl::Context &context) override {
		this->values1.resize(TOTAL_VALUES);
		this->values2.resize(TOTAL_VALUES);
		this->valuesOut.resize(TOTAL_VALUES);

		std::generate(values1.begin(), values1.end(), std::rand);
		std::generate(values2.begin(), values2.end(), std::rand);
	}

	virtual void execute(cl::CommandQueue &queue) override {
		auto &v = this->valuesOut;
		auto &v1 = this->values1;
		auto &v2 = this->values2;

		for (int i=0; i<TOTAL_VALUES; i++) {
			this->valuesOut[i] = v1[i]*v1[i] + 2.0f*v1[i]*v2[i] + v2[i]*v2[i];
		}
	}

private:
	std::vector<float> valuesOut;
	std::vector<float> values1;
	std::vector<float> values2;
};

int main(int argc, char **arg) {

	try {
		auto executer = std::make_unique<TaskExecuter>();
		auto task1 = std::make_unique<ArrayAddTask>();
		auto task2 = std::make_unique<ArrayAddNativeTask>();

		executer->initializeTask(task1.get());
		executer->executeTask(task1.get());

		executer->initializeTask(task2.get());
		executer->executeTask(task2.get());
	} catch (TaskException &exp) {
		std::cout << "TaskException: " <<  exp.what() << std::endl;
	} catch (std::exception &exp) {
		std::cout << "exception: " <<  exp.what() << std::endl;
	}

	
    return 0;
}
