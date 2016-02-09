
#include "KernelCL.hpp"

#include "BufferCL.hpp"
#include <xe/Exception.hpp>

namespace xe { namespace cm {

    KernelCL::KernelCL(const cl::Program &program_, const std::string &kernel_name) {
        program = program_;
        kernel = cl::Kernel(program, kernel_name.c_str());
    }
    
    KernelCL::~KernelCL() {}

    void KernelCL::setArg(const int index, const Buffer *buffer) {
        kernel.setArg(index, static_cast<const BufferCL *>(buffer)->getWrapped());
    }

    void KernelCL::setArg(const int index, const int size, const void *data) {
        kernel.setArg(index, size, data);
    }
}}
