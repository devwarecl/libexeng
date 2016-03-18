
#pragma once

#ifndef __xe_cm_kernelcl_hpp__
#define __xe_cm_kernelcl_hpp__

#include <CL/cl-xe.hpp>
#include <xe/cm/Kernel.hpp>
#include <xe/gfx/GraphicsDriver.hpp>

namespace xe { namespace cm {

    class KernelCL : public Kernel {
    public:
        KernelCL(xe::gfx::GraphicsDriver *graphicsDriver, const cl::Context &context, const cl::Program &program, const std::string &kernel_name);
        
        virtual ~KernelCL();

        virtual void setArg(const int index, const Buffer *buffer) override;

        virtual void setArg(const int index, const int size, const void *data) override;

        virtual void setArg(const int index, const xe::gfx::Image *image) override;

    public:
        cl::Kernel& getWrapped() {
            return kernel;
        }
        
        const cl::Kernel& getWrapped() const {
            return kernel;
        }
        
    private:
        xe::gfx::GraphicsDriver *graphicsDriver = nullptr;
        cl::Context context;
        cl::Program program;
        cl::Kernel kernel;
    };
}}

#endif
