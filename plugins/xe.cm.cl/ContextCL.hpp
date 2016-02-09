
#pragma once

#ifndef __xe_cm_contextcl_hpp__
#define __xe_cm_contextcl_hpp__

#include <CL/cl-xe.hpp>
#include <xe/cm/Context.hpp>

namespace xe { namespace cm {

    class ContextCL : public Context {
    public:
        ContextCL(const cl::Device &device, cl_context_properties *properties);
        
        ~ContextCL();
        
        virtual ComputeLanguage::Enum getLanguage() const override;
        
        virtual BufferPtr createBuffer(Queue *queue, const int size, const void *data) override;
        
        virtual ProgramModulePtr createProgramModule(const std::string &source) override;
        
        virtual ProgramPtr createProgram() override;
        
        virtual KernelPtr createKernel(const Program* program, const std::string &kernel_name) override;
        
        virtual QueuePtr createQueue() override;
        
        cl::Context& getWrapped() {
            return context;
        }
        
        const cl::Context& getWrapped() const {
            return context;
        }
        
    private:
        cl::Device device;
        cl::Context context;
    };    
}}

#endif 
