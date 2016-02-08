
#include "ContextCL.hpp"

#include "BufferCL.hpp"
#include "DeviceCL.hpp"
#include "KernelCL.hpp"
#include "PluginCL.hpp"
#include "ProgramCL.hpp"
#include "ProgramModuleCL.hpp"
#include "QueueCL.hpp"

namespace xe { namespace cm {

    ContextCL::ContextCL(cl::Device &device_, cl_context_properties properties) 
        : device(device_) {
        
        context = cl::Context(device, properties);
    }
    
    ContextCL::~ContextCL() {}
    
    ComputeLanguage::Enum ContextCL::getLanguage() const {
        return ComputeLanguage::OpenCL;
    }
    
    BufferPtr ContextCL::createBuffer(Queue *queue, const int size, const void *data) {
        auto buffer = std::make_unique<BufferCL> (
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
        auto module = std::make_unique<ProgramModuleCL>(source);
        
        return module;
    }
    
    ProgramPtr ContextCL::createProgram() {
        auto program = std::make_unique<ProgramCL>(context);
        
        return program;
    }
    
    KernelPtr ContextCL::createKernel(const Program* program, const std::string &kernel_name) {
        auto kernel = std::make_unique<KernelCL> (
            &static_cast<const ProgramCL*>(program)->getWrapped(),
            kernel_name
        );
        
        return kernel;
    }
    
    QueuePtr ContextCL::createQueue() {
        auto queue = std::make_unique<QueueCL>(context);
        
        return queue;
    }
}}
