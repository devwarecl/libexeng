
#include <xe/Application.hpp>
#include <xe/cm/ComputeManager.hpp>
#include <xe/cm/ComputeModule.hpp>

std::string program_src = R"(
    __kernel void add(__global __write_only int* out, __global __read_only int* in1, __global __read_only int* in2) {
        const int i = get_global_id(0);
        out[i] = in1[i] + in2[i];
    }
)";

class ComputeApplication : public xe::Application {
public:
    ComputeApplication() {
        compute = this->getComputeManager()->createComputeModule();
    }
    
    xe::cm::Device* findDevice() const {
        xe::cm::Device *device = nullptr;
    
        // find device
        auto platforms = compute->enumeratePlatforms();

        std::cout << "Found " << platforms.size() << " platform(s)." << std::endl;
        
        for (xe::cm::Platform *platform : platforms) {
            auto devices = platform->enumerateDevices();
            
            std::cout << "Found " << devices.size() << " device(s)." << std::endl;
            
            for (xe::cm::Device *device_ : devices) {
                auto info = device_->getInfo();
                
                std::cout << "    " << info.getName() << ", " << info.getVendor() << std::endl;
                
                if (!device) {
                    device = device_;
                }
            }
        }
        
        return device;
    }
    
    virtual int run(int argc, char **argv) override {
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
    
private:
    xe::cm::ComputeModulePtr compute;
    xe::cm::ContextPtr context;
    xe::cm::QueuePtr queue;
    xe::cm::ProgramPtr program;
    xe::cm::KernelPtr kernel_add;
};

int main(int argc, char **argv) {
    return xe::Application::execute<ComputeApplication>(argc, argv);
}
