
#include "KernelCL.hpp"

#include "BufferCL.hpp"
#include <xe/Exception.hpp>

namespace xe { namespace cm {

    KernelCL::KernelCL(const cl::Program &program_, const std::string &kernel_name) : program(program_) {
        cl::Kernel kernel = cl::Kernel(program, kernel_name.c_str());
        
        this->kernel = kernel;
    }
    
    KernelCL::~KernelCL() {}

    void KernelCL::setArg(const int index, const Buffer *buffer) {
        if (buffer->getTypeInfo() == TypeId<BufferCL>()) {
            kernel.setArg(0, static_cast<const BufferCL *>(buffer)->getWrapped());
            
        } else {
            EXENG_THROW_EXCEPTION("Invalid buffer");
        }
    }

    void KernelCL::setArg(const int index, const int size, const void *data) {
        kernel.setArg(index, size, data);
    }
}}
