
#include "ContextCL.hpp"

#include "BufferCL.hpp"
#include "DeviceCL.hpp"
#include "KernelCL.hpp"
#include "PluginCL.hpp"
#include "ProgramCL.hpp"
#include "ProgramModuleCL.hpp"
#include "QueueCL.hpp"

namespace xe { namespace cm {

    ContextCL::ContextCL(const cl::Device &device_, cl_context_properties *properties) {
        this->device = device_;
        this->context = cl::Context(device, properties);
    }
    
    ContextCL::~ContextCL() {}
    
    ComputeLanguage::Enum ContextCL::getLanguage() const {
        return ComputeLanguage::OpenCL;
    }
    
    BufferPtr ContextCL::createBuffer(Queue *queue, const int size, const void *data) {
        BufferPtr buffer = std::make_unique<BufferCL> (
            &static_cast<QueueCL*>(queue)->getWrapped(),
            context,
            size
        );
        
        if (data) {
            auto locker = buffer->getLocker(BufferUsage::Write);
            std::memcpy(locker.getPointer(), data, locker.getSize());
        }
        
        return buffer;
    }
    
    ProgramModulePtr ContextCL::createProgramModule(const std::string &source) {
        ProgramModulePtr module = std::make_unique<ProgramModuleCL>(source);
        
        return module;
    }
    
    ProgramPtr ContextCL::createProgram() {
        ProgramPtr program = std::make_unique<ProgramCL>(context, device);
        
        return program;
    }
    
    KernelPtr ContextCL::createKernel(const Program* program, const std::string &kernel_name) {
        KernelPtr kernel = std::make_unique<KernelCL> (
            static_cast<const ProgramCL*>(program)->getWrapped(),
            kernel_name
        );
        
        return kernel;
    }
    
    QueuePtr ContextCL::createQueue() {
        QueuePtr queue = std::make_unique<QueueCL>(context);
        
        return queue;
    }
}}
