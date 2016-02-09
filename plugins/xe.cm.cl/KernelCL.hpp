
#pragma once

#ifndef __xe_cm_kernelcl_hpp__
#define __xe_cm_kernelcl_hpp__

#include <CL/cl-xe.hpp>
#include <xe/cm/Kernel.hpp>

namespace xe { namespace cm {

    class KernelCL : public Kernel {
    public:
        KernelCL(const cl::Program &program, const std::string &kernel_name);
        
        virtual ~KernelCL();

        virtual void setArg(const int index, const Buffer *buffer) override;

        virtual void setArg(const int index, const int size, const void *data) override;

    public:
        cl::Kernel& getWrapped() {
            return kernel;
        }
        
        const cl::Kernel& getWrapped() const {
            return kernel;
        }

    private:
        cl::Program program;
        cl::Kernel kernel;
    };
}}

#endif
