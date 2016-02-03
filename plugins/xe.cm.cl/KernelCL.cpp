
#include "KernelCL.hpp"

namespace xe { namespace cm {
    KernelCL::~KernelCL() {}

    void KernelCL::setArg(const int index, const Buffer *buffer) {
        //! TODO: Missing implementation
    }

    void KernelCL::setArg(const int index, const int size, const void *data) {
        kernel.setArg(index, size, data);
    }
}}
