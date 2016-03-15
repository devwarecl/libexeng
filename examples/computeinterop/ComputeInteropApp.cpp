
#include "ComputeInteropApp.hpp"

#include <xe/cm/ComputeManager.hpp>

std::string program_src = R"(
    __kernel void add(__global __write_only int* out, __global __read_only int* in1, __global __read_only int* in2) {
        const int i = get_global_id(0);
        out[i] = in1[i] + in2[i];
    }
)";

ComputeInteropApplication::ComputeInteropApplication() {
    compute = this->getComputeManager()->createComputeModule();
}
    
xe::cm::Device* ComputeInteropApplication::findDevice() const {
    xe::cm::Device *device = nullptr;
    
    // find device
    auto platforms = compute->enumeratePlatforms();

    std::cout << "Found " << platforms.size() << " platform(s)." << std::endl;
        
    for (xe::cm::Platform *platform : platforms) {
        auto devices = platform->enumerateDevices();
            
        std::cout << "Found " << devices.size() << " device(s)." << std::endl;
            
        for (xe::cm::Device *device_ : devices) {
            auto info = device_->getInfo();
                
            if (device_->getInfo().getType() == xe::cm::DeviceType::GPU) {

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
    
int ComputeInteropApplication::run(int argc, char **argv) {
    xe::cm::Device *device = findDevice();
        
    // prepare host objects
    context = device->createContext();
    queue = context->createQueue();
    program = context->createProgram(program_src);
    kernel_add = context->createKernel(program.get(), "add");
        
    // prepare test data
    const int SIZE = 10;
    const int ARRAY_SIZE = SIZE * sizeof(int);
        
    int out_array[SIZE] = {};
    int in1_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int in2_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        
    xe::BufferPtr out = context->createBuffer(queue.get(), ARRAY_SIZE, nullptr);
    xe::BufferPtr in1 = context->createBuffer(queue.get(), ARRAY_SIZE, in1_array);
    xe::BufferPtr in2 = context->createBuffer(queue.get(), ARRAY_SIZE, in2_array);
        
    // prepare execution of the kernel
    kernel_add->setArg(0, out.get());
    kernel_add->setArg(1, in1.get());
    kernel_add->setArg(2, in2.get());
        
    // execute kernel
    queue->enqueueKernel(kernel_add.get(), SIZE);
        
    // read back the results
    queue->enqueueReadBuffer(out.get(), 0, ARRAY_SIZE, out_array);
        
    // show them in console
    for (int value : out_array) {
        std::cout << value << " ";
    }
        
    std::cout << std::endl;
        
    return 0;
}
